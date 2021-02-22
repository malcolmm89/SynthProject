/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompSynthAudioProcessorEditor::CompSynthAudioProcessorEditor (CompSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), adsr(audioProcessor.vTreeState), masterGain(audioProcessor.vTreeState)
{
    setSize (500, 400);
    oscAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.vTreeState, "OSC", oscSelect);
    addAndMakeVisible(adsr);
    addAndMakeVisible(masterGain);
}

CompSynthAudioProcessorEditor::~CompSynthAudioProcessorEditor()
{
}

//==============================================================================
void CompSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::darkcyan);

}

void CompSynthAudioProcessorEditor::resized()
{
    adsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
    masterGain.setBounds(0, 0, getWidth() / 2, getHeight());
  
}
