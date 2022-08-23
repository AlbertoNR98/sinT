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
    distortion.setDefaultParameters();
    reverb.setDefaultParameters();
}

void FXProcessor::setDistortionParameters(float drive, float range, float blend, float volume)
{
    distortion.setParameters(drive, range, blend, volume);
}

void FXProcessor::setReverbParameters(float roomSize, float width, float damping, float freezeMode, float dryLevel, float wetLevel)
{
    reverb.setParameters(roomSize, width, damping, freezeMode, dryLevel, wetLevel);
}

void FXProcessor::renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    distortion.renderNextBlock(audioBlock);
    reverb.renderNextBlock(audioBlock);
}

void FXProcessor::resetAll()
{
    reverb.resetAll();
}

