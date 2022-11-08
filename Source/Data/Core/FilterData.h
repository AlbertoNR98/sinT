/*
  ==============================================================================

    FilterData.h
    Clase FilterData -> Hereda de juce::dsp::StateVariableTPTFilter<SampleType>
        - Implementa filtros LPF, BPF y HPF

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

static constexpr int LPF{ 0 };
static constexpr int BPF{ 1 };
static constexpr int HPF{ 2 };

class FilterData : public juce::dsp::StateVariableTPTFilter<float>
{
public:
    FilterData();
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setBypassed(const bool filterBypassed);
    bool isBypassed() { return bypassed; };
    void setParameters(const bool bypassed, const int filterMode, const float cutoffFreq, const float filterResonance);
    void renderNextBlock(juce::AudioBuffer<float>& buffer);
    float renderNextSample(int channel, float inputSample);
    

    void resetAll();

private:
    bool bypassed{ false };
    void setMode(const int filterMode);
};
