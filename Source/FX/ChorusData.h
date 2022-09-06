/*
  ==============================================================================

    ChorusData.h
    Clase ChorusData -> Hereda de juce::dsp::Chorus<float>
        - Metodos relacionados con el procesamiento del delay

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>

class ChorusData : public juce::dsp::Chorus<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setDefaultParameters();
    void setParameters(float chorusRate, float chorusDepth, float chorusCentreDelay, float chorusFeedback, float chorusMix);
    bool isBypassed() { return !enabled; }
    void setBypassed(bool bypassValue) { enabled = !bypassValue; }

    void renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock);

    void resetAll();

private:
    juce::dsp::Chorus<float> chorus;
    
    bool enabled = true;

};
