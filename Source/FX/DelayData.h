/*
  ==============================================================================

    DelayData.h
    Clase DelayData -> Hereda de juce::dsp::DelayLine<float>
        - Metodos relacionados con el procesamiento del delay

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DelayData : public juce::dsp::DelayLine<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setDefaultParameters();
    void setParameters(float timeMs, float feedback);
    bool isBypassed() { return !enabled; };
    void setBypassed(bool bypassValue) { enabled = !bypassValue; };

    float getDelayInMiliseconds();
    void setDelayInMiliseconds(float delayInMiliseconds);
    void setMaxDelayInMiliseconds(float maxDelayInMiliseconds);

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples);

    void resetAll();

private:
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delay;
    
    juce::SmoothedValue<float> timeMs{0.0};
    juce::SmoothedValue<float> feedback{0.0};

    float maxDelayInMiliseconds{ 1000.0f };
    double sampleRate{ 44100.0f };
    bool enabled = true;

    juce::dsp::Gain<float> delayGain;
};
