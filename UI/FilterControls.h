/*
  ==============================================================================

    FilterControls.h
    Created: 30 Mar 2021 4:58:57pm
    Author:  malco

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterControls  : public juce::Component
{
public:
    FilterControls(juce::AudioProcessorValueTreeState& vTreeState, juce::String filterTypeId, juce::String filterFreqId, juce::String resoId);
    ~FilterControls() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox filterSelect;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterSelectAttach;

    juce::Slider filterFreqKnob;
    juce::Slider resoKnob;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterFreqAttach;
    juce::Label filterFreaqLabel{ "Filter Freq", "Filter Freq" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resoAttach;
    juce::Label resoLabel{ "Reso", "Reso" };

    void setKnob(juce::Slider& knob, juce::Label& label, juce::AudioProcessorValueTreeState& vTreeState,
        juce::String paramId, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attach);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterControls)
};
