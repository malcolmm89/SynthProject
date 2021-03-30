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
}

void SynthVoice::stopNote(float velocity, bool allowTailOff) 
{
    adsr.noteOff();
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) 
{

}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    adsr.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    osc.prepareToPlay(spec);
    masterGain.prepareToPlay(spec);
    masterGain.prepare(spec);

    masterGain.setGainLinear(0.07f);


    isPerpared = true;
}

void SynthVoice::updateADSR(float attack, float decay, float sustain, float release)
{
    adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::updateGain(float gain)
{
    masterGain.updateGain(gain);
}

void SynthVoice::renderNextBlock(juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) 
{
    jassert(isPerpared); //makes sure prepare to play has been called and is working properly

    if (!isVoiceActive())
    {
        return;
    }

    clickBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    clickBuffer.clear();
    
    juce::dsp::AudioBlock<float> audioBlock{ clickBuffer };

    osc.getNextAudioBlock(audioBlock);
    masterGain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    adsr.applyEnvelopeToBuffer(clickBuffer, 0, clickBuffer.getNumSamples());

    for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
    {
        outputBuffer.addFrom(channel, startSample, clickBuffer, channel, 0, numSamples);

        if (!adsr.isActive())
        {
            clearCurrentNote();
        }
    }
 
}
