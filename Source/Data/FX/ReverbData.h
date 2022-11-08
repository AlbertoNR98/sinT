/*
  ==============================================================================

    ReverbData.h
    Clase ReverbData -> Hereda de juce::dsp::Reverb
        - Metodos relacionados con el procesamiento de la reverberacion

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ReverbData : public juce::dsp::Reverb
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setDefaultParameters();
    void setParameters(bool reverbBypassed, float reverbRoomSize, float reverbWidth, float reverbDamping, float reverbFreezeMode, float reverbDryLevel, float reverbWetLevel);
    bool isBypassed() { return !reverb.isEnabled(); }
    void setBypassed(bool bypassValue) { reverb.setEnabled(!bypassValue); }

    void renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock);

    void resetAll();

private:
    juce::dsp::Reverb reverb;
};
