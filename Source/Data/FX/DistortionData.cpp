/*
  ==============================================================================

    DistortionData.cpp
    Metodos de DistortionData

  ==============================================================================
*/

#include "DistortionData.h"

void DistortionData::setDefaultParameters()
{
    setBypassed(false);
    this->drive = 0.0f;
    this->range = 0.0f;
    this->blend = 0.0f;
}

void DistortionData::setParameters(bool bypassed, float drive, float range, float blend)
{
    setBypassed(bypassed);
    this->drive = drive;
    this->range = range;
    this->blend = blend;
}

void DistortionData::renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    if (isBypassed())
        return;

    for (int channel = 0; channel < audioBlock.getNumChannels(); ++channel)
    {
        for (int sampleIndex = 0; sampleIndex < audioBlock.getNumSamples(); ++sampleIndex)
        {
            float cleanSample = audioBlock.getSample(channel, sampleIndex);
            float distortedSample = cleanSample * drive * range;
            distortedSample = (((2.0f / juce::MathConstants<float>::pi) * atan(distortedSample)) * blend) + (cleanSample * (1.0f - blend));
            audioBlock.setSample(channel, sampleIndex, distortedSample);
        }
    }
}

void DistortionData::resetAll()
{
    // Parametros por defecto
    setDefaultParameters();
}
