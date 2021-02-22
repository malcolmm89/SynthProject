/*
  ==============================================================================

    AdsrData.h
    Created: 21 Feb 2021 9:17:49pm
    Author:  malco

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
    void updateADSR(float attack, float decay, float sustain, float release);

private:
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;

};