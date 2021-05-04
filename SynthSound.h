/*
  ==============================================================================

    SynthSound.h
    Created: 31 Jan 2021 9:26:10pm
    Author:  malco

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound {

public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }
};