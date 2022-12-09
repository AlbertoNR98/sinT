/*
  ==============================================================================

    ReverbComponent.h
    Clase ReverbComponent -> Hereda de juce::Component
        - Parte de la UI relacionada con la reverberacion
            - Controles y attachments asociados a APVTS

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ReverbComponent  : public juce::Component
{
public:
    ReverbComponent(juce::String title, juce::AudioProcessorValueTreeState& apvts, juce::String bypassedId, juce::String roomSizeId, juce::String widthId, juce::String dampingId, juce::String freezeModeId, juce::String dryLevelId, juce::String wetLevelId);
    ~ReverbComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::String title = "";

    juce::ToggleButton bypassedButton;
    juce::Slider roomSizeSlider;
    juce::Slider widthSlider;
    juce::Slider dampingSlider;
    juce::Slider freezeModeSlider;
    juce::Slider dryLevelSlider;
    juce::Slider wetLevelSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassedButtonAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> roomSizeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> widthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dampingAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freezeModeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dryLevelAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetLevelAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};
