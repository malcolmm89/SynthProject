/*
  ==============================================================================

    OscControls.cpp
    Created: 22 Feb 2021 5:07:50pm
    Author:  malco

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscControls.h"

//==============================================================================
OscControls::OscControls(juce::AudioProcessorValueTreeState& vTreeState, juce::String selectorID, juce::String gainId, juce::String fmFreqId, juce::String fmGainId)
{
    juce::StringArray oscArray{ "Sine", "Saw", "Square", "Combo" };
    oscSelector.addItemList(oscArray, 1);
    addAndMakeVisible(oscSelector);
    oscSelectorAttach = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(vTreeState, selectorID, oscSelector);

    setKnob(gainKnob, gainLabel, vTreeState, gainId, gainAttach);
    //fm
    setKnob(fmFreqKnob, fmFreaqLabel, vTreeState, fmFreqId, fmFreqAttach);
    setKnob(fmGainKnob, fmGainLabel, vTreeState, fmGainId, fmGainAttach);
    
}

OscControls::~OscControls()
{
}

void OscControls::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightcoral);
    g.setColour(juce::Colours::white);
    g.drawRect(getLocalBounds());
}

void OscControls::resized()
{
    oscSelector.setBounds(0, 0, 90, 20);
    fmFreqKnob.setBounds(0, 80, 100, 90);
    fmFreaqLabel.setBounds(fmFreqKnob.getX(), fmFreqKnob.getY() - 20, fmFreqKnob.getWidth(), 20);
    fmGainKnob.setBounds(fmFreqKnob.getRight(), 80, 100, 90);
    fmGainLabel.setBounds(fmGainKnob.getX(), fmGainKnob.getY() - 20, fmGainKnob.getWidth(), 20);
    gainKnob.setBounds(50, 150, 100, 90);
}

void OscControls::setKnob(juce::Slider& knob, juce::Label& label, juce::AudioProcessorValueTreeState& vTreeState,
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