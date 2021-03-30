/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompSynthAudioProcessorEditor::CompSynthAudioProcessorEditor (CompSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc(audioProcessor.vTreeState, "OSCTYPE", "FMFREQ", "FMGAIN"), adsr(audioProcessor.vTreeState), masterGain(audioProcessor.vTreeState)
{
    setSize (500, 400);
   
    addAndMakeVisible(osc);
    addAndMakeVisible(adsr);
    //addAndMakeVisible(masterGain);
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
    osc.setBounds(10, 10, 150, 200);
    adsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
    masterGain.setBounds(50, 0, getWidth() / 3, getHeight());
  
}
