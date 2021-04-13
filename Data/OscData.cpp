/*
  ==============================================================================

    OscData.cpp
    Created: 22 Feb 2021 5:07:32pm
    Author:  malco

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{   
    prepare(spec);
    fm.prepare(spec);
    gain.prepare(spec);
}

void OscData::setOscType(int choice)
{
    if (choice == 0) 
    {
        initialise([](float x) {return std::sin(x); }); //Sine
    }
    else if (choice == 1)
    {
        initialise([](float x) {return x / juce::MathConstants<float>::pi; });  //Saw
    }
    else if (choice == 2)
    {
        initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f; }); //Sqaure
    }
    else if (choice == 3)
    {
        initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f * (x / juce::MathConstants<float>::pi); });  //Combo
    }
    else
    {
        jassertfalse; //Something is wrong
    }

}

void OscData::setGain(float gaindB)
{
    gain.setGainDecibels(gaindB);
}

void OscData::setOscFreq(int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmMod);
    lastPlayedNote = midiNoteNumber;
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    for (int i = 0; i < audioBlock.getNumChannels(); i++)
    {
        for (int j = 0; j < audioBlock.getNumSamples(); j++)
        {
            fmMod = fm.processSample(audioBlock.getSample(i, j)) * fmGain;
        }
    }

    process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void OscData::setFmParams(float fGain, float freq)
{
    fm.setFrequency(freq);
    fmGain = fGain;
    //setFrequency(juce::MidiMessage::getMidiNoteInHertz(lastPlayedNote) + fmMod);
    setOscFreq(lastPlayedNote);
}