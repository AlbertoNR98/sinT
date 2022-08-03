/*
  ==============================================================================

    SinTVoice.cpp
    Metodos de SinTVoice

  ==============================================================================
*/

#include "SinTVoice.h"

bool SinTVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SinTVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    osc1.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
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

    osc1.prepare(spec);
    gainOsc1.prepare(spec);

    gainOsc1.setGainLinear(0.4f);

    isPrepared = true;
}

void SinTVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);

    juce::dsp::AudioBlock<float> audioBlock{ outputBuffer };

    osc1.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gainOsc1.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}
