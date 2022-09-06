/*
  ==============================================================================

    ChorusData.cpp
    Metodos de ChorusData

  ==============================================================================
*/

#include "ChorusData.h"

void ChorusData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    resetAll();
    chorus.prepare(spec);
}

void ChorusData::setDefaultParameters()
{
    chorus.setRate(1.0f);
    chorus.setDepth(0.25f);
    chorus.setCentreDelay(7.0f);
    chorus.setFeedback(0.0f);
    chorus.setMix(0.0f);
}

void ChorusData::setParameters(float chorusRate, float chorusDepth, float chorusCentreDelay, float chorusFeedback, float chorusMix)
{
    chorus.setRate(chorusRate);
    chorus.setDepth(chorusDepth);
    chorus.setCentreDelay(chorusCentreDelay);
    chorus.setFeedback(chorusFeedback);
    chorus.setMix(chorusMix);
}

void ChorusData::renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    if (isBypassed())
        return;

    chorus.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void ChorusData::resetAll()
{
    chorus.reset();
}
