/*
  ==============================================================================

    MeterData.h
    Clase MeterData
        - Metodos relacionados con el procesamiento del medidor de ganancia de salida

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class MeterData
{
public:
    const enum Channels
    {
        LeftChannel,
        RightChannel
    };
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setDefaultParameters();

    float getRmsChannelValue(const int channel) const;
    std::pair<float, float> getRmsValues() const;
    
    void renderNextBlock(juce::AudioBuffer<float>& buffer);

private:
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> rmsLevelLeftChannel, rmsLevelRightChannel;
};
