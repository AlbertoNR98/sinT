/*
  ==============================================================================

    FXProcessor.cpp
    Metodos de FXProcessor

  ==============================================================================
*/

#include "FXProcessor.h"

void FXProcessor::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    reverb.prepareToPlay(spec);
    setDefaultParameters();
}

void FXProcessor::setDefaultParameters()
{
    reverb.setDefaultParameters();
}

void FXProcessor::setParameters(float reverbRoomSize, float reverbWidth, float reverbDamping, float reverbFreezeMode, float reverbDryLevel, float reverbWetLevel)
{
    setReverbParameters(reverbRoomSize, reverbWidth, reverbDamping, reverbFreezeMode, reverbDryLevel, reverbWetLevel);
}

void FXProcessor::setReverbParameters(float roomSize, float width, float damping, float freezeMode, float dryLevel, float wetLevel)
{
    reverb.setParameters(roomSize, width, damping, freezeMode, dryLevel, wetLevel);
}

void FXProcessor::renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    reverb.renderNextBlock(audioBlock);
}

void FXProcessor::resetAll()
{
    reverb.resetAll();
}

