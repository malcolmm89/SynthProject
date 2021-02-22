/*
  ==============================================================================

    GainControls.h
    Created: 21 Feb 2021 10:53:21pm
    Author:  malco

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class GainControls  : public juce::Component
{
public:
    GainControls(juce::AudioProcessorValueTreeState& vTreeState);
    ~GainControls() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void setSlider(juce::Slider& slider);
    juce::Slider gainSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainControls)
};
