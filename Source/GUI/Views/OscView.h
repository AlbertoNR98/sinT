/*
  ==============================================================================

    OscView.h
    Created: 20 Oct 2022 7:56:30pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//#include "../Components/ContainerComponent.h"

#include "../Components/OscillatorComponent.h"

//==============================================================================
/*
*/
class OscView  : public juce::Component
{
public:
    OscView(juce::AudioProcessorValueTreeState& apvts, 
        juce::String waveformSelectorId1, juce::String oscGainId1, juce::String oscPitchId1, juce::String fmFreqId1, juce::String fmDepthId1,
        juce::String waveformSelectorId2, juce::String oscGainId2, juce::String oscPitchId2, juce::String fmFreqId2, juce::String fmDepthId2);
    ~OscView() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    OscillatorComponent osc1Component, osc2Component;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscView)
};