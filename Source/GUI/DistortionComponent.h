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

//==============================================================================
/*
*/
class DistortionComponent  : public juce::Component
{
public:
    DistortionComponent(juce::AudioProcessorValueTreeState& apvts, juce::String driveId, juce::String rangeId, juce::String blendId);
    ~DistortionComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider driveSlider;
    juce::Slider rangeSlider;
    juce::Slider blendSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rangeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> blendAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionComponent)
};
