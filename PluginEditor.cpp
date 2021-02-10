/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompSynthAudioProcessorEditor::CompSynthAudioProcessorEditor (CompSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    using sliderAttach = juce::AudioProcessorValueTreeState::SliderAttachment;

    attackAttachment = std::make_unique<sliderAttach>(audioProcessor.vTreeState, "ATTACK", attackSlider);   //apvts, paramID, what we want to attach to
    decayAttachment = std::make_unique<sliderAttach>(audioProcessor.vTreeState, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<sliderAttach>(audioProcessor.vTreeState, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<sliderAttach>(audioProcessor.vTreeState, "RELEASE", releaseSlider);

    oscAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.vTreeState, "OSC", oscSelect);

    setSlider(attackSlider);
    setSlider(decaySlider);
    setSlider(sustainSlider);
    setSlider(releaseSlider);
}

CompSynthAudioProcessorEditor::~CompSynthAudioProcessorEditor()
{
}

//==============================================================================
void CompSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("SHOW ME WHAT YOU'VE GOT!", getLocalBounds(), juce::Justification::centred, 1);
}

void CompSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void CompSynthAudioProcessorEditor::setSlider(juce::Slider& slider) //& refeance so we do not make a copy of slider
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}
