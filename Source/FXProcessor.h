/*
  ==============================================================================

    FXProcessor.h
    Clase FXProcessor
        - Agrupa el procesamiento de todos los efectos

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FX/ReverbData.h"

class FXProcessor
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);

    void setDefaultParameters();
    void setParameters(float reverbRoomSize, float reverbWidth, float reverbDamping, float reverbFreezeMode, float reverbDryLevel, float reverbWetLevel);

    void setReverbParameters(float roomSize, float width, float damping, float freezeMode, float dryLevel, float wetLevel);

    void renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock);

    void resetAll();

private:
    ReverbData reverb;
};