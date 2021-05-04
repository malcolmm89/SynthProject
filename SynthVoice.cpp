/*
  ==============================================================================

    SynthVoice.cpp
    Created: 31 Jan 2021 9:24:42pm
    Author:  malco

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchPosition)
{
    osc.setOscFreq(midiNoteNumber);
    adsr.noteOn();
    filterAdsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();
    filterAdsr.noteOff();
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    osc.prepareToPlay(spec);
    adsr.setSampleRate(sampleRate);
    filter.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    filterAdsr.setSampleRate(sampleRate);

    //masterGain.prepareToPlay(spec);
    //masterGain.prepare(spec);
    masterGain.setGainLinear(0.07f);


    isPerpared = true;
}

void SynthVoice::updateADSR(float attack, float decay, float sustain, float release)
{
    adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::updateGain(float gain)
{
    masterGain.setGain(gain);
}


void SynthVoice::updateFilter(int filterType, float filterFreq, float reso)
{
    float modEnv = filterAdsr.getNextSample();
    filter.setParams(filterType, filterFreq, reso, modEnv);
}

void SynthVoice::updateFilterADSR(float attack, float decay, float sustain, float release)
{
    filterAdsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples)
{
    jassert(isPerpared); //makes sure prepare to play has been called and is working properly

    if (!isVoiceActive())
    {
        return;
    }

    clickBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    filterAdsr.applyEnvelopeToBuffer(clickBuffer, 0, numSamples);
    clickBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock{ clickBuffer };

    osc.getNextAudioBlock(audioBlock);
    adsr.applyEnvelopeToBuffer(clickBuffer, 0, clickBuffer.getNumSamples());
    filter.processFilter(clickBuffer);
    masterGain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
    {
        outputBuffer.addFrom(channel, startSample, clickBuffer, channel, 0, numSamples);

        if (!adsr.isActive())
        {
            clearCurrentNote();
        }
    }
}