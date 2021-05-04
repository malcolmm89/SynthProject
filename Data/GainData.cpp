/*
  ==============================================================================

    GainData.cpp
    Created: 21 Feb 2021 10:53:47pm
    Author:  malco

  ==============================================================================
*/

#include "GainData.h"

void GainData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    prepare(spec);
    masterGain.prepare(spec);
}

void GainData::setGain(float gain)
{
    masterGain.setGainLinear(gain);
};

void GainData::getNextAudioBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    masterGain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}
