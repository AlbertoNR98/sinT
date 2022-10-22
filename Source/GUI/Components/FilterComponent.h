/*
  ==============================================================================

    FilterComponent.h
    Clase FilterComponent -> Hereda de juce::Component
        - Parte de la UI relacionada con el filtro
            - Controles y attachments asociados a APVTS


  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterModeSelectorId, juce::String filterCutoffFreqId, juce::String filterResonanceId);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox filterModeSelector;

    juce::Slider filterCutoffFreqSlider;
    juce::Slider filterResonanceSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterModeSelectorAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterCutoffFreqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterResonanceAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};