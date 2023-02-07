/*
  ==============================================================================

    DistortionComponent.h
    Clase DistortionComponent -> Hereda de juce::Component
        - Parte de la UI relacionada con la distorsion
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
class DistortionComponent  : public juce::Component
{
public:
    DistortionComponent(juce::String title, juce::Colour borderColour, juce::AudioProcessorValueTreeState& apvts, juce::String bypassedId, juce::String driveId, juce::String rangeId, juce::String blendId);
    ~DistortionComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::String title = "";
    juce::Colour distortionBorderColour;

    CustomBypassButton bypassedButton;
    CustomSliderWithLabel driveSlider;
    CustomSliderWithLabel rangeSlider;
    CustomSliderWithLabel blendSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> distortionBypassedButtonAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rangeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> blendAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionComponent)
};
