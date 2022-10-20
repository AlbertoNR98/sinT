/*
  ==============================================================================

    ADSRData.cpp
    Metodos de ADSRData

  ==============================================================================
*/

#include "ADSRData.h"

void ADSRData::update(const float attack, const float decay, const float sustain, const float release)
{
    adsrParameters.attack = attack;
    adsrParameters.decay = decay;
    adsrParameters.sustain = sustain;
    adsrParameters.release = release;

    setParameters(adsrParameters);
}
