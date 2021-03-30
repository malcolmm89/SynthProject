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
    GainControls masterGain;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompSynthAudioProcessorEditor)
};
