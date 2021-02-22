/*
  ==============================================================================

    SynthVoice.h
    Created: 31 Jan 2021 9:24:42pm
    Author:  malco

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/AdsrData.h"
#include "Data/GainData.h"

class SynthVoice : public juce::SynthesiserVoice 
{
// pure virtul functions
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchPosition) override;

    void stopNote(float velocity, bool allowTailOff) override;

    void controllerMoved(int controllerNumber, int newControllerValue) override;

    void pitchWheelMoved(int newPitchWheelValue) override;

    void prepareToPlay(double samplRate, int samplesPerBlock, int outputChannels); //not coming from SynthesiserVoice so do not override

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    void updateADSR(float attack, float decay, float sustain, float release);   //Not pure virtual function

    void updateGain(float gain);


private:

    AdsrData adsr;
    juce::AudioBuffer<float> clickBuffer;

    //juce::dsp::Oscillator<float> osc{ [](float x) {return std::sin(x); } };   //Sine
    
    juce::dsp::Oscillator<float> osc{ [](float x) {return x / juce::MathConstants<float>::pi; } };  //Saw
    
    //juce::dsp::Oscillator<float> osc{ [](float x) {return x < 0.0f ? -1.0f : 1.0f; } };   //Square
    
    //juce::dsp::Oscillator<float> osc{ [](float x) {return x < 0.0f ? -1.0f : 1.0f * (x/juce::MathConstants<float>::pi); } };  //Sqaure * Saw

    GainData masterGain;

    bool isPerpared { false };

};
