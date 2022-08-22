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

    ampAdsr.noteOn();
    filterAdsr.noteOn();
}

void SinTVoice::stopNote(float velocity, bool allowTailOff)
{
    ampAdsr.noteOff();
    filterAdsr.noteOff();

    if (!allowTailOff || !ampAdsr.isActive())
        clearCurrentNote();
}

void SinTVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}

void SinTVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void SinTVoice::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    resetAll();

    ampAdsr.setSampleRate(spec.sampleRate);
    filterAdsr.setSampleRate(spec.sampleRate);

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
    
    // Procesamiento de Filter ADSR
    filterAdsr.applyEnvelopeToBuffer(voiceBuffer, 0, voiceBuffer.getNumSamples());
    filterAdsrOutput = filterAdsr.getNextSample();

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
    ampAdsr.applyEnvelopeToBuffer(voiceBuffer, 0, voiceBuffer.getNumSamples());
    
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

        if (!ampAdsr.isActive()) clearCurrentNote();
    }   
}

void SinTVoice::setFilterModulationParameters(const int filterMode, const float filterCutoffFreq, const float filterResonance, const float filterAdsrDepth)
{
    float cutoffFreqMod = (filterAdsrDepth * filterAdsrOutput) + filterCutoffFreq;
    cutoffFreqMod = std::clamp<float>(cutoffFreqMod, 20.0f, 20000.0f);

    for (int channel = 0; channel < numVoiceChannels; ++channel)
    {
        filter[channel].setParameters(filterMode, cutoffFreqMod, filterResonance);
    }
}

void SinTVoice::resetAll()
{
    voiceGain.reset();
    ampAdsr.reset();
    filterAdsr.reset();
}
