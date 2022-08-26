/*
  ==============================================================================

    DelayData.cpp
    Metodos de DelayData

  ==============================================================================
*/

#include "DelayData.h"

void DelayData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    delay.prepare(spec);
    // Establecer max delay
}

void DelayData::renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    if (!isBypassed()) delay.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

float DelayData::getDelayInMiliseconds()
{
    return 0.f;
}

void DelayData::setDelayInMiliseconds(float delayInMiliseconds)
{
    
}

void DelayData::setMaxDelayInMiliseconds(float maxDelayInMiliseconds)
{

}

void DelayData::resetAll()
{
    delay.reset();
}
