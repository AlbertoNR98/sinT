/*
  ==============================================================================

    ReverbData.cpp
    Metodos de ReverbData

  ==============================================================================
*/

#include "ReverbData.h"

void ReverbData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    resetAll();
    reverb.prepare(spec);
}

void ReverbData::setDefaultParameters()
{
    juce::Reverb::Parameters reverbParameters;

    reverbParameters.roomSize = 0.5f;
    reverbParameters.width = 1.0f;
    reverbParameters.damping = 0.5f;
    reverbParameters.freezeMode = 0.0f;
    reverbParameters.dryLevel = 1.0f;
    reverbParameters.wetLevel = 0.0f;

    reverb.setParameters(reverbParameters);
}

void ReverbData::setParameters(float reverbRoomSize, float reverbWidth, float reverbDamping, float reverbFreezeMode, float reverbDryLevel, float reverbWetLevel)
{
    juce::Reverb::Parameters reverbParameters;

    reverbParameters.roomSize = reverbRoomSize;
    reverbParameters.width = reverbWidth;
    reverbParameters.damping = reverbDamping;
    reverbParameters.freezeMode = reverbFreezeMode;
    reverbParameters.dryLevel = reverbDryLevel;
    reverbParameters.wetLevel = reverbWetLevel;

    reverb.setParameters(reverbParameters);
}

void ReverbData::renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    if (isBypassed()) 
        return;
    
    reverb.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void ReverbData::resetAll()
{
    reverb.reset();
}
