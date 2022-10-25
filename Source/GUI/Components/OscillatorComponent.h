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

//==============================================================================
/*
*/
class OscillatorComponent  : public juce::Component
{
public:
    OscillatorComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String waveformSelectorId, juce::String oscGainId, juce::String oscPitchId, juce::String fmFreqId, juce::String fmDepthId);
    ~OscillatorComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::String oscName;

    juce::ComboBox oscWaveSelector;

    juce::Slider oscGainSlider;
    juce::Slider oscPitchSlider;
    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> oscGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> oscPitchAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmFreqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmDepthAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorComponent)
};
