/*
  ==============================================================================

    SinTVoice.cpp
    Metodos de SinTVoice

  ==============================================================================
*/

#include "SinTVoice.h"

bool SinTVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return true;
}

void SinTVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{

}

void SinTVoice::stopNote(float velocity, bool allowTailOff)
{

}

void SinTVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}

void SinTVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void SinTVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = outputChannels;
}

void SinTVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    juce::dsp::AudioBlock<float> audioBlock{ outputBuffer };
}
