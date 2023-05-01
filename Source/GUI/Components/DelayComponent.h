/*
  ==============================================================================

    DelayComponent.h
    Clase DelayComponent -> Hereda de juce::Component
        - Parte de la UI relacionada con el efecto de delay
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
class DelayComponent  : public juce::Component
{
public:
    DelayComponent(juce::String title, juce::Colour borderColour, juce::AudioProcessorValueTreeState& apvts, juce::String bypassedId, juce::String timeMsId, juce::String feedbackId);
    ~DelayComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::String title = "";
    juce::Colour delayBorderColour;

    CustomBypassButton bypassedButton;
    CustomSliderWithLabel timeMsSlider;
    CustomSliderWithLabel feedbackSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassedButtonAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> timeMsAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayComponent)
};
