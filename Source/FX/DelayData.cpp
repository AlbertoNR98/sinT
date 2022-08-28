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
    delayGain.setGainLinear(0.1f);
    setDefaultParameters();
}

void DelayData::setParameters(float timeMs, float feedback)
{
    this->timeMs = timeMs;
    this->feedback = feedback;
    setDelayInMiliseconds(timeMs);
}

void DelayData::setDefaultParameters()
{
    maxDelayInMiliseconds = 1000.0f;
    delay.setDelay(sampleRate / 2);
    delay.setMaximumDelayInSamples(sampleRate);
}

float DelayData::getDelayInMiliseconds()
{
    return delay.getDelay() / (sampleRate * 1000);
}

void DelayData::setDelayInMiliseconds(float delayInMiliseconds)
{
    delay.setDelay((delayInMiliseconds / 1000.f) * sampleRate);
    DBG(delayInMiliseconds);
}

void DelayData::setMaxDelayInMiliseconds(float maxDelayInMiliseconds)
{
    delay.setMaximumDelayInSamples((maxDelayInMiliseconds / 1000.f) * sampleRate);
}

void DelayData::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    if (isBypassed() || timeMs == 0.0f || feedback == 0.0f)
        return;
    
    setDelayInMiliseconds(timeMs);

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        auto* inSamples = outputBuffer.getReadPointer(channel);
        auto* outSamples = outputBuffer.getWritePointer(channel);

        for (int sampleIndex = 0; sampleIndex < outputBuffer.getNumSamples(); ++sampleIndex)
        {
            float delayedSample = delay.popSample(channel);
            float inDelay = inSamples[sampleIndex] + (feedback * delayedSample);
            delayGain.processSample(inDelay);
            delay.pushSample(channel, inDelay);
            outSamples[sampleIndex] = inSamples[sampleIndex] + delayedSample;
        }
    }
}

void DelayData::resetAll()
{
    delay.reset();
}
