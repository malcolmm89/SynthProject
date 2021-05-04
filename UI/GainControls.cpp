/*
  ==============================================================================

    GainControls.cpp
    Created: 21 Feb 2021 10:53:21pm
    Author:  malco

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GainControls.h"

//==============================================================================
GainControls::GainControls(juce::AudioProcessorValueTreeState& vTreeState)
{
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(vTreeState, "GAIN", gainSlider);
    setSlider(gainSlider);
}

GainControls::~GainControls()
{
}

void GainControls::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkcyan);

    
}

void GainControls::resized()
{
    auto bounds = getLocalBounds().reduced(10);
    auto padding = 10;
    auto sliderWidth = bounds.getWidth() / 4 - padding;
    auto sliderHeight = bounds.getHeight();
    auto sliderXPosition = 20;
    auto sliderYPosition = 0;
    auto labelOffset = 20;
    auto labelHeight = 20;
    auto labelStart = sliderYPosition - labelOffset;;

    gainSlider.setBounds(sliderXPosition, sliderYPosition, sliderWidth, sliderHeight);

}

void GainControls::setSlider(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}
