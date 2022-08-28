/*
  ==============================================================================

    DelayData.cpp
    Metodos de DelayData

  ==============================================================================
*/

#include "DelayData.h"

void DelayData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    resetAll();
    sampleRate = spec.sampleRate;
    delay.prepare(spec);
    setDefaultParameters();
}

void DelayData::setDefaultParameters()
{
    maxDelayInMiliseconds = 1000.0f;
    delay.setDelay(sampleRate / 2);
    setMaxDelayInMiliseconds(maxDelayInMiliseconds);
}

float DelayData::getDelayInMiliseconds()
{
    return delay.getDelay() / (sampleRate * 1000);
}

void DelayData::setDelayInMiliseconds(float delayInMiliseconds)
{
    delay.setDelay((delayInMiliseconds / 1000.f) * sampleRate);
}

void DelayData::setMaxDelayInMiliseconds(float maxDelayInMiliseconds)
{
    delay.setMaximumDelayInSamples((maxDelayInMiliseconds / 1000.f) * sampleRate);
}

void DelayData::renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    if (!isBypassed())
    {
        delayBuffer.setSize(audioBlock.getNumChannels(), 2 * audioBlock.getNumSamples(), false, false, true);
        audioBlock.copyTo(delayBuffer);

        for (int channel = 0; channel < audioBlock.getNumChannels(); ++channel)
        {
            auto* inSamples = delayBuffer.getReadPointer(channel);
            auto* outSamples = delayBuffer.getWritePointer(channel);

            for (int sampleIndex = 0; sampleIndex < audioBlock.getNumSamples(); ++sampleIndex)
            {
                float delayedSample = delay.popSample(channel);
                float inDelay = inSamples[sampleIndex] + (0.5 * delayedSample); // Feedback = 0.5
                delay.pushSample(channel, inDelay);
                outSamples[sampleIndex] = inSamples[sampleIndex] + delayedSample;

                /*
                float cleanSample = audioBlock.getSample(channel, sampleIndex);
                float distortedSample = cleanSample * drive * range;
                distortedSample = (((2.0f / juce::float_Pi) * atan(distortedSample)) * blend) + (cleanSample * (1.0f - blend));
                audioBlock.setSample(channel, sampleIndex, distortedSample);
                */
            }
        }
        audioBlock.copyFrom(delayBuffer);
    }
}

void DelayData::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    //outputBuffer.setSize(outputBuffer.getNumChannels(), 2 * outputBuffer.getNumSamples(), true, true, false);
    int delayTimeSamples = 0.2 * sampleRate;    // 0.5 = Time
    delay.setDelay(delayTimeSamples);

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        auto* inSamples = outputBuffer.getReadPointer(channel);
        auto* outSamples = outputBuffer.getWritePointer(channel);

        for (int sampleIndex = 0; sampleIndex < outputBuffer.getNumSamples(); ++sampleIndex)
        {
            float delayedSample = delay.popSample(channel);
            float inDelay = inSamples[sampleIndex] + (0.9 * delayedSample); // Feedback = 0.5
            delay.pushSample(channel, inDelay);
            outSamples[sampleIndex] = inSamples[sampleIndex] + delayedSample;
        }
    }
}

void DelayData::resetAll()
{
    delay.reset();
}
