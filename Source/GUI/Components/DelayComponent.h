/*
  ==============================================================================

    DelayComponent.h
    Created: 25 Aug 2022 4:37:17pm
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
class DelayComponent  : public juce::Component
{
public:
    DelayComponent(juce::String title, juce::AudioProcessorValueTreeState& apvts, juce::String bypassedId, juce::String timeMsId, juce::String feedbackId);
    ~DelayComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::String title = "";

    juce::ToggleButton bypassedButton;
    CustomSliderWithLabel timeMsSlider;
    CustomSliderWithLabel feedbackSlider;

    //juce::Slider timeMsSlider;
    //juce::Slider feedbackSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassedButtonAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> timeMsAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayComponent)
};
