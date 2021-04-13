/*
==============================================================================

FilterData.h
Created : 30 Mar 2021 4 : 58 : 25pm
Author : malco

==============================================================================
*/

#pragma once

//#include "OscData.h"
#include <JuceHeader.h>

class FilterData : public juce::dsp::StateVariableTPTFilter<float>
{
public:
    void prepareToPlay(double samplesRate, int samplesPerBlock, int numChannels);    //info needed for filter
    void processFilter(juce::AudioBuffer<float>& filterBuffer);
    void setParams(int filterType, float filterFreq, float reso, float modEnv = 1.0f);
    void reset();

private:
    juce::dsp::StateVariableTPTFilter<float> filter;
    bool isPrepared{ false };
};