/*
  ==============================================================================

    OscillatorComponent.h
    OscillatorComponent class -> Inherits from juce::Component
        - Part of the UI related to the oscillators
            - Controls and attachments associated with APVTS

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Assets/ColorPalette.h"
#include "../Assets/CustomControls.h"
#include "../Assets/CustomLookAndFeel.h"
#include "../Source/ParamsIDList.h"

//==============================================================================
/*
*/
class OscillatorComponent : public juce::Component, virtual CustomLookAndFeel
{
public:
    OscillatorComponent(juce::String name, juce::Colour borderColour, juce::AudioProcessorValueTreeState& apvts, juce::String bypassedId, juce::String waveformSelectorId, juce::String oscGainId, juce::String oscPitchId, juce::String fmFreqId, juce::String fmDepthId);
    ~OscillatorComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::String oscName;
    juce::Colour oscBorderColour;

    CustomBypassButton oscBypassedButton;

    juce::ComboBox oscWaveSelector;

    CustomSliderWithLabel oscGainSlider;
    CustomSliderWithLabel oscPitchSlider;
    CustomSliderWithLabel fmFreqSlider;
    CustomSliderWithLabel fmDepthSlider;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> oscBypassedButtonAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> oscGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> oscPitchAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmFreqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmDepthAttachment;

    void setupWaveformSelector(bool bypassed = false);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorComponent)
};
