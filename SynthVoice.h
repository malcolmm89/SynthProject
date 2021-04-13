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
#include "Data/OscData.h"
#include "Data/FilterData.h"

class SynthVoice : public juce::SynthesiserVoice 
{
// pure virtul functions
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchPosition) override;

    void stopNote(float velocity, bool allowTailOff) override;

    void controllerMoved(int controllerNumber, int newControllerValue) override;

    void pitchWheelMoved(int newPitchWheelValue) override;

    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels); //not coming from SynthesiserVoice so do not override

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    void updateADSR(float attack, float decay, float sustain, float release);   //Not pure virtual function

    //void updateGain(float gain);

    //void updateFilter(int filterType, float filterFreq, float reso);

    OscData& getOsc() { return osc; }

    GainData& getGain() { return masterGain; }

    //FilterData& getFilter() { return filter; }

private:

    AdsrData adsr;
    juce::AudioBuffer<float> clickBuffer;
    OscData osc;
    GainData masterGain;
    //FilterData filter;

    bool isPerpared { false };

};
