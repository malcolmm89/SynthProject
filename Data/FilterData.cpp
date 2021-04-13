/*
  ==============================================================================

    FilterData.cpp
    Created: 30 Mar 2021 4:58:25pm
    Author:  malco

  ==============================================================================
*/

#include "FilterData.h"

void FilterData::prepareToPlay(double samplesRate, int samplesPerBlock, int numChannels)
{
    filter.reset();

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = samplesRate;
    spec.numChannels = numChannels;
    filter.prepare(spec);

    isPrepared = true;
}

void FilterData::processFilter(juce::AudioBuffer<float>& filterBuffer)
{
    jassert(isPrepared);
    juce::dsp::AudioBlock<float> block{ filterBuffer };
    filter.process(juce::dsp::ProcessContextReplacing<float> { block });    //replaces data in buffer
}

void FilterData::setParams(int filterType, float filterFreq, float reso, float modEnv)
{

    if (filterType == 0)
    {
        filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
    }
    else if (filterType == 1)
    {
        filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
    }
    else if (filterType == 2)
    {
        filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
    }
    else
    {
        jassertfalse; //Something is wrong
    }

    float freqEnv = filterFreq * modEnv;
    freqEnv = std::fmax(freqEnv, 20.0f);    //returns greatest value
    freqEnv = std::fmin(freqEnv, 20000.0f); //returns smallest value

    filter.setCutoffFrequency(freqEnv);
    filter.setResonance(reso);
}

/*
void FilterData::selectFilter(int choice)
{
    if (choice == 0)
    {
        setType(juce::dsp::StateVariableTPTFilterType::lowpass);
    }
    else if (choice == 1)
    {
        setType(juce::dsp::StateVariableTPTFilterType::highpass);
    }
    else if (choice == 2)
    {
        setType(juce::dsp::StateVariableTPTFilterType::bandpass);
    }
    else
    {
        jassertfalse; //Something is wrong
    }
}
*/

void FilterData::reset()
{
    filter.reset();
}