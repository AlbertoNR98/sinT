/*
  ==============================================================================

    LFOComponent.h
    Clase LFOComponent -> Hereda de juce::Component
        - Parte de la UI relacionada con el LFO
            - Controles y attachments asociados a APVTS

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LFOComponent  : public juce::Component
{
public:
    LFOComponent(juce::AudioProcessorValueTreeState& apvts, juce::String lfoFreqId, juce::String lfoDepthId);
    ~LFOComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider lfoFreqSlider;
    juce::Slider lfoDepthSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lfoFreqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lfoDepthAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOComponent)
};
