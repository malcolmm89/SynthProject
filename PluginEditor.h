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
    AdsrControls adsr;
    GainControls masterGain;
    juce::ComboBox oscSelect;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompSynthAudioProcessorEditor)
};
