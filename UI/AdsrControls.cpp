/*
  ==============================================================================

    AdsrControls.cpp
    Created: 21 Feb 2021 9:19:36pm
    Author:  malco

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrControls.h"

//==============================================================================
AdsrControls::AdsrControls(juce::String name, juce::AudioProcessorValueTreeState& vTreeState, juce::String attackId, juce::String decatyId, juce::String sustainId, juce::String releaseId)
{
    controlsName = name;
    setSlider(attackSlider, attackLabel, vTreeState, attackId, attackAttachment);
    setSlider(decaySlider, decayLabel, vTreeState, decatyId, decayAttachment);
    setSlider(sustainSlider, sustainLabel, vTreeState, sustainId, sustainAttachment);
    setSlider(releaseSlider, releaseLabel, vTreeState, releaseId, releaseAttachment);
}

AdsrControls::~AdsrControls()
{
}

void AdsrControls::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);
    
    g.fillAll(juce::Colours::darkcyan);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText(controlsName, labelSpace.withX(5), juce::Justification::left);
    g.drawRect(getLocalBounds());
}

void AdsrControls::resized()
{
    auto bounds = getLocalBounds().reduced(10);
    auto padding = 10;
    auto sliderWidth = bounds.getWidth() / 4 - padding;
    auto sliderHeight = bounds.getHeight();
    auto sliderXPosition = 0;
    auto sliderYPosition = 0;
    auto labelOffset = 20;
    auto labelHeight = 20;
    auto labelStart = sliderYPosition - labelOffset;

    attackSlider.setBounds(sliderXPosition, sliderYPosition, sliderWidth, sliderHeight);
    attackLabel.setBounds(attackSlider.getX(), labelStart, sliderWidth, labelHeight);

    decaySlider.setBounds(attackSlider.getRight() + padding, sliderYPosition, sliderWidth, sliderHeight);
    decayLabel.setBounds(decaySlider.getX(), labelStart, sliderWidth, labelHeight);

    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderYPosition, sliderWidth, sliderHeight);
    sustainLabel.setBounds(sustainSlider.getX(), labelStart, sliderWidth, labelHeight);

    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderYPosition, sliderWidth, sliderHeight);
    releaseLabel.setBounds(releaseSlider.getX(), labelStart, sliderWidth, labelHeight);
}

using sliderAttach = juce::AudioProcessorValueTreeState::SliderAttachment;

void AdsrControls::setSlider(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& vTreeState, juce::String paramId, std::unique_ptr<sliderAttach>& attach)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);

    attach = std::make_unique<sliderAttach>(vTreeState, paramId, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(20.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}
