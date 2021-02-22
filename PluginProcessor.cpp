/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//#include "SynthVoice.h"
//#include "SynthSound.h"

//==============================================================================
CompSynthAudioProcessor::CompSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()            //initsalizer list
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), vTreeState(*this, nullptr, "Parameters", createParams())  //AudioProcessor &processorToConnectTo,                               UndoManager *undoManagerToUse, const Identifier &valueTreeType, ParameterLayout parameterLayout
#endif                                                                              //refrence tp processor want to connect to (one we are in right now), not using undoManager,         what we call the value tree,     createParams returns ParameterLayout      
{
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
}

CompSynthAudioProcessor::~CompSynthAudioProcessor()
{
    //.addVoice - The object passed in will be managed by the synthesiser, which will delete it later on when no longer needed. The caller should not retain a pointer to the voice.
}

//==============================================================================
const juce::String CompSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CompSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CompSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CompSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CompSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CompSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CompSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CompSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String CompSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void CompSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void CompSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    synth.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void CompSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CompSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void CompSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))      //auto = SynthVoice*
        {
            auto& attack = *vTreeState.getRawParameterValue("ATTACK");      //auto = struct std::atomic<float>
            auto& decay = *vTreeState.getRawParameterValue("DECAY");        //.getRawParameterValue retutns pointer, 
            auto& sustain = *vTreeState.getRawParameterValue("SUSTAIN");    //& makes a refernce to pointer
            auto& release = *vTreeState.getRawParameterValue("RELEASE");
            auto& gain = *vTreeState.getRawParameterValue("GAIN");

            voice->updateADSR(attack, decay, sustain, release); //atomic /////// -> access members of a structure through a pointer (. for pointer)
            voice->updateGain(gain);

            //Osc controls
            //ADSR
            //LFO
        }
    }
       
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    /*
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
    */

}

//==============================================================================
bool CompSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CompSynthAudioProcessor::createEditor()
{
    return new CompSynthAudioProcessorEditor (*this);
}

//==============================================================================
void CompSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CompSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CompSynthAudioProcessor();
}

// Value Tree
juce::AudioProcessorValueTreeState::ParameterLayout CompSynthAudioProcessor::createParams()
{
    juce::StringArray oscArray{"Sine", "Saw", "Square", "Combo"};

    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    //Switch Oscillators
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC", "osc", oscArray, 1));

    //Attack
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> { 0.01f, 1.0f, }, 0.1f));    //paramID, paramName, paramRange, defaultValue

    //Decay
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float> { 0.01f, 1.0f, }, 0.1f));

    //Sustain
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float> { 0.01f, 1.0f, }, 0.1f));

    //Release
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float> { 0.01f, 3.0f, }, 0.4f));
    
    //Gain
    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "gain", juce::NormalisableRange<float> { 0.0f, 1.0f, }, 0.3f));    //paramID, paramName, minValue, maxvalue, defaultValue

    return { params.begin(), params.end() };

}