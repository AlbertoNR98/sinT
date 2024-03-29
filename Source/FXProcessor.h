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

    void setDistortionParameters(bool bypassed, float drive, float range, float mix);
    void setChorusParameters(bool bypassed, float rate, float depth, float centreDelay, float feedback, float mix);
    void setDelayParameters(bool bypassed, float timeMs, float feedback);
    void setReverbParameters(bool bypassed, bool freezeMode, float roomSize, float width, float damping, float dryLevel, float wetLevel);

    void renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock);

    void resetAll();

private:
    DistortionData distortion;
    ChorusData chorus;
    DelayData delay;
    ReverbData reverb;
};
