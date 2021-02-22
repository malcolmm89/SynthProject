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
AdsrControls::AdsrControls(juce::AudioProcessorValueTreeState& vTreeState)
{
    using sliderAttach = juce::AudioProcessorValueTreeState::SliderAttachment;

    attackAttachment = std::make_unique<sliderAttach>(vTreeState, "ATTACK", attackSlider);   //apvts, paramID, what we want to attach to
    decayAttachment = std::make_unique<sliderAttach>(vTreeState, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<sliderAttach>(vTreeState, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<sliderAttach>(vTreeState, "RELEASE", releaseSlider);
    //gainAttachment = std::make_unique<sliderAttach>(vTreeState, "GAIN", masterGain);

    setSlider(attackSlider);
    setSlider(decaySlider);
    setSlider(sustainSlider);
    setSlider(releaseSlider);

}

AdsrControls::~AdsrControls()
{
}

void AdsrControls::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::firebrick);
}

void AdsrControls::resized()
{
    auto bounds = getLocalBounds().reduced(10);
    auto padding = 10;
    auto sliderWidth = bounds.getWidth() / 4 - padding;
    auto sliderHeight = bounds.getHeight();
    auto sliderXPosition = 0;
    auto sliderYPosition = 0;


    attackSlider.setBounds(sliderXPosition, sliderYPosition, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, sliderYPosition, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderYPosition, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderYPosition, sliderWidth, sliderHeight);

}

void AdsrControls::setSlider(juce::Slider& slider) //& refeance so we do not make a copy of slider
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}
