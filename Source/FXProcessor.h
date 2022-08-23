/*
  ==============================================================================

    FXProcessor.h
    Clase FXProcessor
        - Agrupa el procesamiento de todos los efectos

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FX/DistortionData.h"
#include "FX/ReverbData.h"

class FXProcessor
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);

    void setDefaultParameters();

    void setDistortionParameters(float drive, float range, float blend, float volume);
    void setReverbParameters(float roomSize, float width, float damping, float freezeMode, float dryLevel, float wetLevel);

    void renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock);

    void resetAll();

private:
    DistortionData distortion;
    ReverbData reverb;
};