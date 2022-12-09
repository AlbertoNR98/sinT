/*
  ==============================================================================

    ChorusComponent.h
    Created: 6 Sep 2022 11:43:47am
    Author:  Alberto Naranjo

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
class ChorusComponent  : public juce::Component
{
public:
    ChorusComponent(juce::String title, juce::AudioProcessorValueTreeState& apvts, juce::String bypassedId, juce::String rateId, juce::String depthId, juce::String centreDelayId, juce::String feedbackId, juce::String mixId);
    ~ChorusComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::String title = "";

    juce::ToggleButton bypassedButton;
    CustomSliderWithLabel rateSlider;
    CustomSliderWithLabel depthSlider;
    CustomSliderWithLabel centreDelaySlider;
    CustomSliderWithLabel feedbackSlider;
    CustomSliderWithLabel mixSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassedButtonAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> depthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> centreDelayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusComponent)
};
