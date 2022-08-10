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
    OscillatorComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveformSelectorId, juce::String oscGainId, juce::String oscPitchId);
    ~OscillatorComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox oscWaveSelector;

    juce::Slider oscGainSlider;
    juce::Slider oscPitchSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> oscGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> oscPitchAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorComponent)
};
