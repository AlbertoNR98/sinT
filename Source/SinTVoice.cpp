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
    adsr.noteOn();
}

void SinTVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();
    if (!allowTailOff || !adsr.isActive())
        clearCurrentNote();
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

    adsr.setSampleRate(sampleRate);

    // Valores de prueba -> Sustituir por APVTS
    adsrParams.attack = 0.8f;
    adsrParams.decay = 0.8f;
    adsrParams.sustain = 1.0f;
    adsrParams.release = 1.5f;
    adsr.setParameters(adsrParams);

    gainOsc1.setGainLinear(0.4f);

    isPrepared = true;
}

void SinTVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);

    if (!isVoiceActive()) return; 

    auto audioBlock = juce::dsp::AudioBlock<float>(outputBuffer).getSubBlock(startSample, numSamples);

    osc1.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gainOsc1.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
    
    for(int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
        if (!adsr.isActive())
            clearCurrentNote();
}
