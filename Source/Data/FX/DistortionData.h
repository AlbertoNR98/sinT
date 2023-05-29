/*
  ==============================================================================

    DistortionData.h
    Clase DistortionData
        - Metodos relacionados con el procesamiento de la distorsion

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DistortionData
{
public:
    bool isBypassed() { return bypassed; }
    void setBypassed(bool bypassValue) { bypassed = bypassValue; }

    void setDefaultParameters();
    void setParameters(bool bypassed, float drive, float range, float mix);

    void renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock);
    
    void resetAll();

private:
    bool bypassed{ false };

    float drive;
    float range;
    float mix;
};
