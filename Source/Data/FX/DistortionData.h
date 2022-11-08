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
    void setDefaultParameters();
    void setParameters(bool bypassed, float drive, float range, float blend);
    bool isBypassed() { return bypassed; }
    void setBypassed(bool bypassValue) { bypassed = !bypassValue; }

    void renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock);
    
    void resetAll();

private:
    float drive;
    float range;
    float blend;
    bool bypassed = false;
};
