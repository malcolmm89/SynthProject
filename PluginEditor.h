/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

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
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    void setSlider(juce::Slider& slider);

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    juce::Slider oscSelect;

    CompSynthAudioProcessor& audioProcessor;    //refernce to audio processor

    using sliderAttach = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<sliderAttach> attackAttachment;
    std::unique_ptr<sliderAttach> decayAttachment;
    std::unique_ptr<sliderAttach> sustainAttachment;
    std::unique_ptr<sliderAttach> releaseAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompSynthAudioProcessorEditor)
};
