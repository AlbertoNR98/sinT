/*
  ==============================================================================

    ADSRData.cpp
    Metodos de ADSRData

  ==============================================================================
*/

#include "ADSRData.h"

void ADSRData::update(const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;

    setParameters(adsrParams);
}
