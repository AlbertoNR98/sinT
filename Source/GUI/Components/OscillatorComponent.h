/*
  ==============================================================================

    OscillatorComponent.h
    Clase OscillatorComponent -> Hereda de juce::Component
        - Parte de la UI relacionada con los osciladores
            - Controles y attachments asociados a APVTS

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Assets/ColorPalette.h"
#include "../Assets/CustomControls.h"
#include "../Source/ParamsIDList.h"

//==============================================================================
/*
*/
class OscillatorComponent  : public juce::Component
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
