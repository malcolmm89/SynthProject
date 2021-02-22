/*
  ==============================================================================

    GainData.h
    Created: 21 Feb 2021 10:53:47pm
    Author:  malco

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class GainData : public juce::dsp::Gain<float>
{
public:
    void updateGain(float gain);

private:
    juce::dsp::Gain<float> masterGain;

};
