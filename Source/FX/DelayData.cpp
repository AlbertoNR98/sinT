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
    delayGain.prepare(spec);
    delayGain.setGainLinear(1.0f);
    setDefaultParameters();
}

void DelayData::setParameters(float timeMs, float feedback)
{
    this->timeMs = timeMs;
    this->feedback = feedback;
    setDelayInMiliseconds(this->timeMs.getCurrentValue());
}

void DelayData::setDefaultParameters()
{
    delay.setMaximumDelayInSamples(2 * sampleRate * (maxDelayInMiliseconds / 1000.0f));
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

void DelayData::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    if (isBypassed() || timeMs.getCurrentValue() == 0.0f || feedback.getCurrentValue() == 0.0f)
    {
        resetAll();
        return;
    } 

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        auto* inputSampleReadPointer = outputBuffer.getReadPointer(channel);
        auto* outputSampleWritePointer = outputBuffer.getWritePointer(channel);

        for (int sampleIndex = 0; sampleIndex < outputBuffer.getNumSamples(); ++sampleIndex)
        {
            setDelayInMiliseconds(timeMs.getNextValue());
            float delayedSample = delay.popSample(channel);
            float inputDelayBuffer = inputSampleReadPointer[sampleIndex] + (feedback.getNextValue() * delayedSample);
            delay.pushSample(channel, inputDelayBuffer);
            outputSampleWritePointer[sampleIndex] = delayGain.processSample(inputSampleReadPointer[sampleIndex] + delayedSample);
        }
    }
}

void DelayData::resetAll()
{
    delay.reset();
}
