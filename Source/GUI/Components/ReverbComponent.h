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
#include "../Assets/ColorPalette.h"
#include "../Assets/CustomLookAndFeel.h"
#include "../Assets/CustomControls.h"
#include "../Source/ParamsIDList.h"

//==============================================================================
/*
*/
class ReverbComponent : public juce::Component, virtual CustomLookAndFeel
{
public:
    ReverbComponent(juce::String title, juce::Colour borderColour, juce::AudioProcessorValueTreeState& apvts, juce::String bypassedId, juce::String roomSizeId, juce::String widthId, juce::String dampingId, juce::String freezeModeId, juce::String dryLevelId, juce::String wetLevelId);
    ~ReverbComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::String title = "";
    juce::Colour reverbBorderColour;

    CustomBypassButton bypassedButton;
    juce::TextButton freezeModeButton;

    CustomSliderWithLabel roomSizeSlider;
    CustomSliderWithLabel widthSlider;
    CustomSliderWithLabel dampingSlider;
    CustomSliderWithLabel dryLevelSlider;
    CustomSliderWithLabel wetLevelSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassedButtonAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> freezeModeButtonAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> roomSizeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> widthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dampingAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dryLevelAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetLevelAttachment;

    void setupFreezeModeButton(bool bypassed = false);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};
