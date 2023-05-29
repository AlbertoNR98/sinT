/*
  ==============================================================================

    FXProcessor.cpp
    Metodos de FXProcessor

  ==============================================================================
*/

#include "FXProcessor.h"

void FXProcessor::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    chorus.prepareToPlay(spec);
    delay.prepareToPlay(spec);
    reverb.prepareToPlay(spec);
    setDefaultParameters();
}

void FXProcessor::setDefaultParameters()
{
    distortion.setDefaultParameters();
    chorus.setDefaultParameters();
    delay.setDefaultParameters();
    reverb.setDefaultParameters();
}

void FXProcessor::setDistortionParameters(bool bypassed, float drive, float range, float mix)
{
    distortion.setParameters(bypassed, drive, range, mix);
}

void FXProcessor::setChorusParameters(bool bypassed, float rate, float depth, float centreDelay, float feedback, float mix)
{
    chorus.setParameters(bypassed, rate, depth, centreDelay, feedback, mix);
}

void FXProcessor::setDelayParameters(bool bypassed, float timeMs, float feedback)
{
    delay.setParameters(bypassed, timeMs, feedback);
}

void FXProcessor::setReverbParameters(bool bypassed, bool freezeMode, float roomSize, float width, float damping, float dryLevel, float wetLevel)
{
    reverb.setParameters(bypassed, freezeMode, roomSize, width, damping, dryLevel, wetLevel);
}

void FXProcessor::renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    distortion.renderNextBlock(audioBlock);
    chorus.renderNextBlock(audioBlock);
    delay.renderNextBlock(audioBlock);
    reverb.renderNextBlock(audioBlock);
}

void FXProcessor::resetAll()
{
    delay.resetAll();
    reverb.resetAll();
}
