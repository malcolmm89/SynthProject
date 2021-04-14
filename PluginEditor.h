/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AdsrControls.h"
#include "UI/GainControls.h"
#include "UI/OscControls.h"
#include "UI/FilterControls.h"

//==============================================================================
/**
*/
class CompSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    CompSynthAudioProcessorEditor (CompSynthAudioProcessor&);
    ~CompSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    CompSynthAudioProcessor& audioProcessor;    //refernce to audio processor
    OscControls osc;
    AdsrControls adsr;
    FilterControls filter;
    AdsrControls filterAdsr;
    GainControls masterGain;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompSynthAudioProcessorEditor)
};
