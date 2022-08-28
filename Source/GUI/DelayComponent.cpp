/*
  ==============================================================================

    DelayComponent.cpp
    Created: 25 Aug 2022 4:37:17pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DelayComponent.h"

//==============================================================================
DelayComponent::DelayComponent(juce::AudioProcessorValueTreeState& apvts, juce::String timeMsId, juce::String feedbackId)
{
    timeMsSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(timeMsSlider);

    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(feedbackSlider);

    timeMsAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, timeMsId, timeMsSlider);
    feedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, feedbackId, feedbackSlider);
}

DelayComponent::~DelayComponent()
{
}

void DelayComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black); 
}

void DelayComponent::resized()
{
    timeMsSlider.setBounds(0, 0, 300, 30);
    feedbackSlider.setBounds(0, timeMsSlider.getBottom(), 300, 30);
}
