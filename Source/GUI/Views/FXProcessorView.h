/*
  ==============================================================================

    FXProcessorView.h
    Clase FXProcessorView -> Hereda de juce::Component
        - Vista FX

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Assets/ColorPalette.h"
#include "../Assets/CustomLookAndFeel.h"
#include "../Components/DistortionComponent.h"
#include "../Components/ChorusComponent.h"
#include "../Components/DelayComponent.h"
#include "../Components/ReverbComponent.h"

//==============================================================================
/*
*/
class FXProcessorView : public juce::Component, virtual CustomLookAndFeel
{
public:
    FXProcessorView(juce::AudioProcessorValueTreeState& apvts,
        juce::String distortionBypassed, juce::String distortionDrive, juce::String distortionRange, juce::String distortionMix,
        juce::String chorusBypassed, juce::String chorusRate, juce::String chorusDepth, juce::String chorusCentreDelay, juce::String chorusFeedback, juce::String chorusMix,
        juce::String delayBypassed, juce::String delayTimeMs, juce::String delayFeedback,
        juce::String reverbBypassed, juce::String reverbRoomSize, juce::String reverbWidth, juce::String reverbDamping, juce::String reverbFreezeMode, juce::String reverbDryLevel, juce::String reverbWetLevel);
    ~FXProcessorView() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::String viewTitle = "FX Processor";

    DistortionComponent distortionComponent;
    ChorusComponent chorusComponent;
    DelayComponent delayComponent;
    ReverbComponent reverbComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FXProcessorView)
};
