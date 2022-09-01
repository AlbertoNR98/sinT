/*
  ==============================================================================

    MeterData.h
    Clase MeterData
        - Metodos relacionados con el procesamiento del medidor de ganancia de salida

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

static constexpr int leftChannel{ 0 };
static constexpr int rightChannel{ 1 };

class MeterData
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setDefaultParameters();

    float getRmsChannelValue(const int channel) const;
    std::pair<float, float> getRmsValues() const;
    
    void renderNextBlock(juce::AudioBuffer<float>& buffer);

private:
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> rmsLevelLeftChannel, rmsLevelRightChannel;
};
