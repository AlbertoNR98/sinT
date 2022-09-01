/*
  ==============================================================================

    MeterData.cpp
    Metodos de la clase MeterData

  ==============================================================================
*/

#include "MeterData.h"

void MeterData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    rmsLevelLeftChannel.reset(spec.sampleRate, 0.2);
    rmsLevelRightChannel.reset(spec.sampleRate, 0.2);
}

void MeterData::setDefaultParameters()
{
    rmsLevelLeftChannel.setCurrentAndTargetValue(-100.0f);
    rmsLevelRightChannel.setCurrentAndTargetValue(-100.0f);
}

float MeterData::getRmsChannelValue(const int channel) const
{
    if (channel == leftChannel)
    {
        return rmsLevelLeftChannel.getCurrentValue();
    }
    else if (channel == rightChannel)
    {
        return rmsLevelRightChannel.getCurrentValue();
    }
    else
    {
        return 0.0f;
    }
}

std::pair<float, float> MeterData::getRmsValues() const
{
    return std::make_pair<float, float>(rmsLevelLeftChannel.getCurrentValue(), rmsLevelRightChannel.getCurrentValue());
}

void MeterData::renderNextBlock(juce::AudioBuffer<float>& buffer)
{
    rmsLevelLeftChannel.skip(buffer.getNumSamples());
    rmsLevelRightChannel.skip(buffer.getNumSamples());

    const auto newRmsLeftChannelValue = juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
    if (newRmsLeftChannelValue < rmsLevelLeftChannel.getCurrentValue())
    {
        rmsLevelLeftChannel.setTargetValue(newRmsLeftChannelValue);
    }
    else
    {
        rmsLevelLeftChannel.setCurrentAndTargetValue(newRmsLeftChannelValue);
    }

    const auto newRmsRightChannelValue = juce::Decibels::gainToDecibels(buffer.getRMSLevel(1, 0, buffer.getNumSamples()));
    if (newRmsRightChannelValue < rmsLevelRightChannel.getCurrentValue())
    {
        rmsLevelRightChannel.setTargetValue(newRmsRightChannelValue);
    }
    else
    {
        rmsLevelRightChannel.setCurrentAndTargetValue(newRmsRightChannelValue);
    }
}
