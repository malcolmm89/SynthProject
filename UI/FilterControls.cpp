/*
  ==============================================================================

    FilterControls.cpp
    Created: 30 Mar 2021 4:58:57pm
    Author:  malco

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterControls.h"

//==============================================================================
FilterControls::FilterControls(juce::AudioProcessorValueTreeState& vTreeState, juce::String filterTypeId, juce::String filterFreqId, juce::String resoId)
{
    juce::StringArray filterArray{ "Low Pass", "High Pass", "Band Pass" };
    filterSelect.addItemList(filterArray, 1);
    addAndMakeVisible(filterSelect);
    filterSelectAttach = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(vTreeState, filterTypeId, filterSelect);

    setKnob(filterFreqKnob, filterFreaqLabel, vTreeState, filterFreqId, filterFreqAttach);
    setKnob(resoKnob, resoLabel, vTreeState, resoId, resoAttach);
}

FilterControls::~FilterControls()
{
}

void FilterControls::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkcyan);
    g.setColour(juce::Colours::white);
    g.drawRect(getLocalBounds());
}

void FilterControls::resized()
{
    filterSelect.setBounds(0, 0, 120, 20);
    filterFreqKnob.setBounds(0, 80, 100, 90);
    filterFreaqLabel.setBounds(filterFreqKnob.getX(), filterFreqKnob.getY() - 20, filterFreqKnob.getWidth(), 20);
    resoKnob.setBounds(filterFreqKnob.getRight(), 80, 100, 90);
    resoLabel.setBounds(resoKnob.getX(), resoKnob.getY() - 20, resoKnob.getWidth(), 20);

}

void FilterControls::setKnob(juce::Slider& knob, juce::Label& label, juce::AudioProcessorValueTreeState& vTreeState,
    juce::String paramId, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attach)
{
    knob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    knob.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(knob);
    attach = std::make_unique< juce::AudioProcessorValueTreeState::SliderAttachment>(vTreeState, paramId, knob);
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(20.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}