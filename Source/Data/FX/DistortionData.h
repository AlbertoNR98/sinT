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
    void setParameters(float drive, float range, float blend);
    bool isBypassed() { return !enabled; }
    void setBypassed(bool bypassValue) { enabled = !bypassValue; }

    void renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock);
    
    void resetAll();

private:
    float drive;
    float range;
    float blend;
    bool enabled = true;
};
