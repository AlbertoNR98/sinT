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
    for (int channel = 0; channel < numVoiceChannels; channel++)
    {
        osc1[channel].setWaveFreq(midiNoteNumber);
        osc2[channel].setWaveFreq(midiNoteNumber);
    }

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
    resetAll();

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = outputChannels;

    adsr.setSampleRate(sampleRate);

    for (int channel = 0; channel < numVoiceChannels; channel++)
    {
        osc1[channel].prepareToPlay(spec);
        osc2[channel].prepareToPlay(spec);
        filter[channel].prepare(spec);
    }

    voiceGain.prepare(spec);
    voiceGain.setGainLinear(0.1f);
}

void SinTVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    if (!isVoiceActive()) return; 

    voiceBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    voiceBuffer.clear();

    // Procesamiento de voz
    for (int channel = 0; channel < voiceBuffer.getNumChannels(); ++channel)
    {
        for (int sampleIndex = 0; sampleIndex < voiceBuffer.getNumSamples(); ++sampleIndex)
        {
            float sampleUnprocessed = voiceBuffer.getSample(channel, sampleIndex);
            float sampleProcessed = osc1[channel].renderNextSample(sampleUnprocessed) + osc2[channel].renderNextSample(sampleUnprocessed);
            voiceBuffer.setSample(channel, sampleIndex, sampleProcessed);
        }
    }
   
    // Procesamiento de ganancia
    voiceGain.process(juce::dsp::ProcessContextReplacing<float>(juce::dsp::AudioBlock<float>{voiceBuffer}));
    
    // Procesamiento de AMP ADSR
    adsr.applyEnvelopeToBuffer(voiceBuffer, 0, voiceBuffer.getNumSamples());
    
    // Procesamiento de filtro
    for (int channel = 0; channel < voiceBuffer.getNumChannels(); ++channel)
    {
        for (int sampleIndex = 0; sampleIndex < voiceBuffer.getNumSamples(); ++sampleIndex)
        {
            float sampleUnprocessed = voiceBuffer.getSample(channel, sampleIndex);
            float sampleProcessed = filter[channel].renderNextSample(channel, sampleUnprocessed);
            voiceBuffer.setSample(channel, sampleIndex, sampleProcessed);
        }
    }

    // Agrega al buffer de salida
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, voiceBuffer, channel, 0, numSamples);

        if (!adsr.isActive()) clearCurrentNote();
    }   
}

void SinTVoice::setModParameters(const int filterMode, const float filterCutoffFreq, const float filterResonance)
{
    //TO-DO -> MOD ADSR
    for (int channel = 0; channel < numVoiceChannels; ++channel)
    {
        filter[channel].setParameters(filterMode, filterCutoffFreq, filterResonance);
    }
}

void SinTVoice::resetAll()
{
    voiceGain.reset();
    adsr.reset();
}
