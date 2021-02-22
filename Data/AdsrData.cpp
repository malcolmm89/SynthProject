/*
  ==============================================================================

    AdsrData.cpp
    Created: 21 Feb 2021 9:17:49pm
    Author:  malco

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::updateADSR(float attack, float decay, float sustain, float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;

    setParameters(adsrParams);
};