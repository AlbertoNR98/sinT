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
    if (!isBypassed()) delay.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void DelayData::resetAll()
{
    delay.reset();
}
