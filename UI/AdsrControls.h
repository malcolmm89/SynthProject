/*
  ==============================================================================

    AdsrControls.h
    Created: 21 Feb 2021 9:19:36pm
    Author:  malco

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrControls  : public juce::Component
{
public:
    AdsrControls(juce::AudioProcessorValueTreeState& vTreeState);
    ~AdsrControls() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void setSlider(juce::Slider& slider);
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    using sliderAttach = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<sliderAttach> attackAttachment;
    std::unique_ptr<sliderAttach> decayAttachment;
    std::unique_ptr<sliderAttach> sustainAttachment;
    std::unique_ptr<sliderAttach> releaseAttachment;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrControls)
};
