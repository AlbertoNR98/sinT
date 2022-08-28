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
    delay.prepareToPlay(spec);
    setDefaultParameters();
}

void FXProcessor::setDefaultParameters()
{
    distortion.setDefaultParameters();
    delay.setDefaultParameters();
    reverb.setDefaultParameters();
}

void FXProcessor::setDistortionParameters(float drive, float range, float blend)
{
    distortion.setParameters(drive, range, blend);
}

void FXProcessor::setDelayParameters(float timeMs, float feedback)
{
    delay.setParameters(timeMs, feedback);
}

void FXProcessor::setReverbParameters(float roomSize, float width, float damping, float freezeMode, float dryLevel, float wetLevel)
{
    reverb.setParameters(roomSize, width, damping, freezeMode, dryLevel, wetLevel);
}

void FXProcessor::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    juce::dsp::AudioBlock<float> audioBlock{ outputBuffer };
    distortion.renderNextBlock(audioBlock);
    delay.renderNextBlock(outputBuffer, startSample, numSamples);
    reverb.renderNextBlock(audioBlock);
}

void FXProcessor::resetAll()
{
    delay.resetAll();
    reverb.resetAll();
}

