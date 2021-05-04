/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompSynthAudioProcessor::CompSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()            //initsalizer list
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ), vTreeState(*this, nullptr, "Parameters", createParams())  //AudioProcessor &processorToConnectTo,                               UndoManager *undoManagerToUse, const Identifier &valueTreeType, ParameterLayout parameterLayout
#endif                                                                              //refrence tp processor want to connect to (one we are in right now), not using undoManager,         what we call the value tree,     createParams returns ParameterLayout      
{
    synth.addSound(new SynthSound());

    for (int i = 0; i < 6; i++)
    {
        synth.addVoice(new SynthVoice());
    }
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

void CompSynthAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String CompSynthAudioProcessor::getProgramName(int index)
{
    return {};
}

void CompSynthAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void CompSynthAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
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
bool CompSynthAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
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

void CompSynthAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))      //auto = SynthVoice*
        {
            auto& oscType = *vTreeState.getRawParameterValue("OSCTYPE");
            auto& oscGain = *vTreeState.getRawParameterValue("OSCGAIN");
            auto& fmFreq = *vTreeState.getRawParameterValue("FMFREQ");
            auto& fmGain = *vTreeState.getRawParameterValue("FMGAIN");

            auto& attack = *vTreeState.getRawParameterValue("ATTACK");      //auto = struct std::atomic<float>
            auto& decay = *vTreeState.getRawParameterValue("DECAY");        //.getRawParameterValue retutns pointer, 
            auto& sustain = *vTreeState.getRawParameterValue("SUSTAIN");    //& makes a refernce to pointer
            auto& release = *vTreeState.getRawParameterValue("RELEASE");    //* gets value pointed to by pointer

            auto& filterType = *vTreeState.getRawParameterValue("FILTERTYPE");
            auto& filterFreq = *vTreeState.getRawParameterValue("FILTERFREQ");
            auto& reso = *vTreeState.getRawParameterValue("RESO");

            auto& filterAttack = *vTreeState.getRawParameterValue("FILATTACK");      
            auto& filterDecay = *vTreeState.getRawParameterValue("FILDECAY");         
            auto& filterSustain = *vTreeState.getRawParameterValue("FILSUSTAIN");    
            auto& filterRelease = *vTreeState.getRawParameterValue("FILRELEASE");

            //auto& gain = *vTreeState.getRawParameterValue("GAIN");

            voice->getOsc().setOscType(oscType);
            voice->getOsc().setGain(oscGain);
            voice->getOsc().setFmParams(fmGain, fmFreq);
            voice->updateADSR(attack, decay, sustain, release); /////// -> access members of a structure through a pointer (. for pointer)
            voice->updateFilter(filterType, filterFreq, reso);
            voice->updateFilterADSR(filterAttack, filterDecay, filterSustain, filterRelease);
            //voice->updateGain(gain);
        }

    }

    for (const juce::MidiMessageMetadata metadata : midiMessages)
    {
        if (metadata.numBytes == 3)
        {
            juce::Logger::writeToLog("SampleStamp: " + metadata.getMessage().getDescription());
        }
    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

}

//==============================================================================
bool CompSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CompSynthAudioProcessor::createEditor()
{
    return new CompSynthAudioProcessorEditor(*this);
}

//==============================================================================
void CompSynthAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CompSynthAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
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
    juce::StringArray oscArray{ "Sine", "Saw", "Square", "Combo" };
    juce::StringArray filterArray{ "Low Pass", "High Pass", "Band Pass" };

    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    //Osc Select
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSCTYPE", "Osc1", oscArray, 1));
    //Osc Gain
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSCGAIN", "Osc Gain", juce::NormalisableRange<float> { -40.0f, 1.0f, 0.1f, }, 1.0f));
    //FM
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FMFREQ", "FM Freq", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01f, 0.25f}, 0.0f));
    //FM Gain
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FMGAIN", "FM Gain", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01f, 0.25f}, 0.0f));

    //Attack
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> { 0.01f, 1.0f, }, 0.1f));    //paramID, paramName, paramRange, defaultValue
    //Decay
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float> { 0.01f, 1.0f, }, 0.1f));
    //Sustain
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float> { 0.01f, 1.0f, }, 1.0f));
    //Release
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float> { 0.01f, 3.0f, }, 0.4f));

    //Filter Attack
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILATTACK", "FilAttack", juce::NormalisableRange<float> { 0.01f, 1.0f, }, 0.01f));    //paramID, paramName, paramRange, defaultValue
    //Filter Decay
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILDECAY", "FilDecay", juce::NormalisableRange<float> { 0.01f, 1.0f, }, 0.01f));
    //Filter Sustain
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILSUSTAIN", "FilSustain", juce::NormalisableRange<float> { 0.01f, 1.0f, }, 1.0f));
    //Filter Release
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILRELEASE", "FilRelease", juce::NormalisableRange<float> { 0.01f, 3.0f, }, 0.01f));

    //Filter Select
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type", filterArray, 0));
    //Filter Freq
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERFREQ", "Filter Freq", juce::NormalisableRange<float> { 20.0f, 20000.0f, 0.1f, 0.6f, }, 200.0f));
    //Resonence
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RESO", "Reso", juce::NormalisableRange<float> { 0.1f, 10.0f, 0.1f, }, 0.1f));

    //Gain
    //params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "gain", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f, }, 0.07f)); 

    return { params.begin(), params.end() };

}