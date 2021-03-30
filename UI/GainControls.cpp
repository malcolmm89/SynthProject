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
    g.fillAll(juce::Colours::dodgerblue);

    
}

void GainControls::resized()
{
    auto bounds = getLocalBounds().reduced(10);
    auto padding = 10;
    auto sliderWidth = bounds.getWidth() / 4 - padding;
    auto sliderHeight = bounds.getHeight();
    auto sliderXPosition = 0;
    auto sliderYPosition = 0;

    gainSlider.setBounds(sliderXPosition, sliderYPosition, sliderWidth, sliderHeight);

}

void GainControls::setSlider(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}
