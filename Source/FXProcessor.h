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
#include "FX/DelayData.h"
#include "FX/ReverbData.h"

class FXProcessor
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);

    void setDefaultParameters();

    void setDistortionParameters(float drive, float range, float blend);
    void setReverbParameters(float roomSize, float width, float damping, float freezeMode, float dryLevel, float wetLevel);

    void renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock);
    
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples);

    void resetAll();

private:
    DistortionData distortion;
    DelayData delay;
    ReverbData reverb;
};