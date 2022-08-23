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
    void setParameters(float drive, float range, float blend, float volume);
    bool isEnabled() { return enabled; }
    void setEnabled(bool enableValue) { enabled = enableValue; }

    void renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock);
    
    void resetAll();

private:
    float drive;
    float range;
    float blend;
    float volume;
    bool enabled = true;
};
