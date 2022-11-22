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
    //juce::Slider mainGainSlider;
    juce::ToggleButton portamentoButton;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mainGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> portamentoButtonAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainControlComponent)
};
