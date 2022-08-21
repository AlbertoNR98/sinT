/*
  ==============================================================================

    GainComponent.h
    Clase GainComponent -> Hereda de juce::Component
        - Parte de la UI relacionada con la ganancia general
            - Controles y attachments asociados a APVTS

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class GainComponent  : public juce::Component
{
public:
    GainComponent(juce::AudioProcessorValueTreeState& apvts, juce::String mainGainId);
    ~GainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider mainGainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mainGainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainComponent)
};
