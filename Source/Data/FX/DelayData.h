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
    void setParameters(bool bypassed, float timeMs, float feedback);
    bool isBypassed() { return bypassed; };
    void setBypassed(bool bypassValue) { bypassed = bypassValue; };

    void setDelayInMiliseconds(float delayInMiliseconds);
    void setMaxDelayInMiliseconds(float maxDelayInMiliseconds);

    void renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock);

    void resetAll();

private:
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delay;
    
    float timeMs{0.0};
    float feedback{0.0};

    float maxDelayInMiliseconds{ 1000.0f };
    double sampleRate{ 44100.0f };

    bool bypassed{ true };
};
