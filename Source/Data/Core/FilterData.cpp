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
    prepare(spec);
}

void FilterData::setBypassed(const bool filterBypassed)
{
    bypassed = filterBypassed;
}

void FilterData::setParameters(const bool bypassed, const int filterMode, const float cutoffFreq, const float filterResonance)
{
    setBypassed(bypassed);
    setCutoffFrequency(cutoffFreq);
    setResonance(filterResonance);
    setMode(filterMode);
}

void FilterData::renderNextBlock(juce::AudioBuffer<float>& buffer)
{
    if (isBypassed()) return;

    juce::dsp::AudioBlock<float> audioBlock{ buffer };
    process(juce::dsp::ProcessContextReplacing<float>{audioBlock});
}

float FilterData::renderNextSample(int channel, float inputSample)
{
    if (isBypassed()) return inputSample;

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
