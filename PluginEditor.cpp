/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompSynthAudioProcessorEditor::CompSynthAudioProcessorEditor (CompSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc(audioProcessor.vTreeState, "OSCTYPE", "OSCGAIN", "FMFREQ", "FMGAIN"), 
        adsr("Amp Env", audioProcessor.vTreeState, "ATTACK", "DECAY", "SUSTAIN", "RELEASES"), 
        masterGain(audioProcessor.vTreeState), 
        filter(audioProcessor.vTreeState, "FILTERTYPE", "FILTERFREQ", "RESO"),
        filterAdsr("Filter Env", audioProcessor.vTreeState, "FILATTACK", "FILDECAY", "FILSUSTAIN", "FILRELEASE")
{
    setSize (1000, 600);
   
    addAndMakeVisible(osc);
    addAndMakeVisible(adsr);
    addAndMakeVisible(filter);
    addAndMakeVisible(filterAdsr);
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
    osc.setBounds(10, 10, 200, 300);
    adsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight() / 2);
    filter.setBounds(osc.getRight(), 10, 200, 300);
    filterAdsr.setBounds(filter.getRight(), getHeight() / 2, getWidth() / 2, getHeight() / 2);
    //masterGain.setBounds(50, 0, getWidth() / 3, getHeight());
  
}
