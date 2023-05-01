/*
  ==============================================================================

    MainControlComponent.h
    Clase MainControlComponent -> Hereda de juce::Component
        - Parte de la UI relacionada con los controles generales
            - Controles y attachments asociados a APVTS

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Assets/CustomControls.h"
#include "../Assets/ColorPalette.h"

//==============================================================================
/*
*/
class MainControlComponent  : public juce::Component
{
public:
    MainControlComponent(juce::AudioProcessorValueTreeState& apvts, juce::String mainGainId, juce::String portamentoId);
    ~MainControlComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    CustomSliderWithLabel mainGainSlider;
    juce::TextButton portamentoButton;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mainGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> portamentoButtonAttachment;

    void setupGainSlider();
    void setupPortamentoButton();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainControlComponent)
};
