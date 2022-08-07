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
    OscillatorComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveformSelectorId);
    ~OscillatorComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox osc1WaveSelector;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> osc1WaveSelectorAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorComponent)
};
