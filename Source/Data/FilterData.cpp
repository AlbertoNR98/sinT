/*
  ==============================================================================

    FilterData.cpp
    Metodos de la clase FilterData

  ==============================================================================
*/

#include "FilterData.h"

FilterData::FilterData()
{
    setType(juce::dsp::StateVariableTPTFilterType::lowpass);
}

void FilterData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    reset();
    prepare(spec);
}

void FilterData::setParameters(const int filterMode, const float cutoffFreq, const float filterResonance)
{
    setMode(filterMode);
    setCutoffFrequency(cutoffFreq);
    setResonance(filterResonance);
}

void FilterData::renderNextBlock(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> audioBlock{ buffer };
    process(juce::dsp::ProcessContextReplacing<float>{audioBlock});
}

float FilterData::renderNextSample(int channel, float inputSample)
{
    return processSample(channel, inputSample);
}

void FilterData::setMode(const int filterMode)
{
    switch (filterMode)
    {
    case LPF:
        setType(juce::dsp::StateVariableTPTFilterType::lowpass);
        break;
    case BPF:
        setType(juce::dsp::StateVariableTPTFilterType::bandpass);
        break;
    case HPF:
        setType(juce::dsp::StateVariableTPTFilterType::highpass);
        break;
    default:
        setType(juce::dsp::StateVariableTPTFilterType::lowpass);
        break;
    }
}

void FilterData::resetAll()
{
    reset();
}
