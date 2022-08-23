/*
  ==============================================================================

    DistortionData.cpp
    Metodos de DistortionData

  ==============================================================================
*/

#include "DistortionData.h"

void DistortionData::setDefaultParameters()
{
    // Revisar
    this->drive = 1.0f;
    this->range = 1.0f;
    this->blend = 1.0f;
    this->volume = 1.0f;
}

void DistortionData::setParameters(float drive, float range, float blend, float volume)
{
    this->drive = drive;
    this->blend = blend;
    this->range = range;
    this->volume = volume;
}

void DistortionData::renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    if (!enabled)
        return;

    for (int channel = 0; channel < audioBlock.getNumChannels(); ++channel)
    {
        for (int sampleIndex = 0; sampleIndex < audioBlock.getNumSamples(); ++sampleIndex)
        {
            float cleanSample = audioBlock.getSample(channel, sampleIndex);
            float distortedSample = cleanSample * drive * range;
            distortedSample = (((((2.0f / juce::float_Pi) * atan(distortedSample)) * blend) + (cleanSample * (1.0f - blend))) / 2.0f) * volume;
            audioBlock.setSample(channel, sampleIndex, distortedSample);
        }
    }
}

void DistortionData::resetAll()
{
    // Parametros por defecto
    setDefaultParameters();

    // Limpia el buffer -> TO-DO
}
