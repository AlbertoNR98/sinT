/*
  ==============================================================================

    FXProcessor.h
    Clase FXProcessor
        - Agrupa el procesamiento de todos los efectos

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Data/FX/DistortionData.h"
#include "Data/FX/ChorusData.h"
#include "Data/FX/DelayData.h"
#include "Data/FX/ReverbData.h"

class FXProcessor
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);

    void setDefaultParameters();

    void setDistortionParameters(float drive, float range, float blend);
    void setChorusParameters(float rate, float depth, float centreDelay, float feedback, float mix);
    void setDelayParameters(float timeMs, float feedback);
    void setReverbParameters(float roomSize, float width, float damping, float freezeMode, float dryLevel, float wetLevel);

    void renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock);

    void resetAll();

private:
    DistortionData distortion;
    ChorusData chorus;
    DelayData delay;
    ReverbData reverb;
};