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
    AdsrControls(juce::String name, juce::AudioProcessorValueTreeState& vTreeState, juce::String attackId, juce::String decatyId, juce::String sustainId, juce::String releaseId);
    ~AdsrControls() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //void setSlider(juce::Slider& slider);
    
    using sliderAttach = juce::AudioProcessorValueTreeState::SliderAttachment;

    void setSlider(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& vTreeState, juce::String paramId, std::unique_ptr<sliderAttach>& attach);

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    std::unique_ptr<sliderAttach> attackAttachment;
    std::unique_ptr<sliderAttach> decayAttachment;
    std::unique_ptr<sliderAttach> sustainAttachment;
    std::unique_ptr<sliderAttach> releaseAttachment;
    
    juce::Label attackLabel{ "Attack", "A" };
    juce::Label decayLabel{ "Decay", "D" };
    juce::Label sustainLabel{ "Sustain", "S" };
    juce::Label releaseLabel{ "Release", "R" };

    juce::String controlsName{ "" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrControls)
};
