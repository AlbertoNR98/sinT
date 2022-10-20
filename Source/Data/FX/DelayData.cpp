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

void DelayData::setParameters(float timeMs, float feedback)
{
    this->timeMs = timeMs;
    this->feedback = feedback;
    setDelayInMiliseconds(this->timeMs);
}

void DelayData::setDefaultParameters()
{
    delay.setMaximumDelayInSamples(sampleRate * std::ceil(maxDelayInMiliseconds / 1000.0f));
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
    if (isBypassed() || timeMs == 0.0f || feedback == 0.0f)
    {
        resetAll();
        return;
    }

    for (int channel = 0; channel < audioBlock.getNumChannels(); ++channel)
    {
        for (int sampleIndex = 0; sampleIndex < audioBlock.getNumSamples(); ++sampleIndex)
        {
            float delayedSample = delay.popSample(channel);
            float inputSample = audioBlock.getSample(channel, sampleIndex);
            float inputDelayBuffer = inputSample + (feedback * delayedSample);
            delay.pushSample(channel, inputDelayBuffer);
            audioBlock.setSample(channel, sampleIndex, inputDelayBuffer);
        }
    }
}

void DelayData::resetAll()
{
    delay.reset();
}
