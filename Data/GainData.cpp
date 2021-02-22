/*
  ==============================================================================

    GainData.cpp
    Created: 21 Feb 2021 10:53:47pm
    Author:  malco

  ==============================================================================
*/

#include "GainData.h"

void GainData::updateGain(float gain)
{
    masterGain.setGainLinear(gain);
};
