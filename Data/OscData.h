/*
  ==============================================================================

    OscData.h
    Created: 22 Feb 2021 5:07:32pm
    Author:  malco

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setOscType(int choice);
    void setOscFreq(int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& audioBlock);
    void setFmParams(float gain, float freq);

private:
    juce::dsp::Oscillator<float> fm { [](float x) {return std::sin(x); } };
    float fmMod{ 0.0f };
    float fmGain{ 0.0f };
    int lastPlayedNote{ 0 };
};
