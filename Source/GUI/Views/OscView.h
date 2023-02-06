/*
  ==============================================================================

    OscView.h

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../Assets/ColorPalette.h"
#include "../Components/OscillatorComponent.h"

//==============================================================================
/*
*/
class OscView  : public juce::Component
{
public:
    OscView(juce::AudioProcessorValueTreeState& apvts, 
        juce::String bypassedId1, juce::String waveformSelectorId1, juce::String oscGainId1, juce::String oscPitchId1, juce::String fmFreqId1, juce::String fmDepthId1,
        juce::String bypassedId2, juce::String waveformSelectorId2, juce::String oscGainId2, juce::String oscPitchId2, juce::String fmFreqId2, juce::String fmDepthId2);
    ~OscView() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::String viewTitle = "Oscillators";

    OscillatorComponent osc1Component, osc2Component;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscView)
};
