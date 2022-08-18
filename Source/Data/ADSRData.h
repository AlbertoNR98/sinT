/*
  ==============================================================================

    ADSRData.h
    Clase ADSRData -> Hereda de juce::ADSR
        - Metodos relacionados con el procesamiento de ADSR

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ADSRData : public juce::ADSR
{
public:
    void update(const float attack, const float decay, const float sustain, const float release);

private:
    juce::ADSR::Parameters adsrParameters;
};
