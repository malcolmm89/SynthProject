/*
  ==============================================================================

    OscControls.h
    Created: 22 Feb 2021 5:07:50pm
    Author:  malco

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscControls  : public juce::Component
{
public:
    OscControls(juce::AudioProcessorValueTreeState& vTreeState, juce::String selectorID, juce::String gainId, juce::String fmFreqId, juce::String fmGainId);
    ~OscControls() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox oscSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelectorAttach;

    juce::Slider gainKnob;
    juce::Slider fmFreqKnob;
    juce::Slider fmGainKnob;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttach;
    juce::Label gainLabel{ "Gain", "Gain" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmFreqAttach;
    juce::Label fmFreaqLabel{ "Fm Freq", "fm Freq" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmGainAttach;
    juce::Label fmGainLabel{ "fm Gain", "fm Gain" };

    void setKnob(juce::Slider& knob, juce::Label& label, juce::AudioProcessorValueTreeState& vTreeState,
        juce::String paramId, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attach);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscControls)
};
