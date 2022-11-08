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
DelayComponent::DelayComponent(juce::AudioProcessorValueTreeState& apvts, juce::String bypassedId, juce::String timeMsId, juce::String feedbackId)
{
    addAndMakeVisible(bypassedButton);

    timeMsSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(timeMsSlider);

    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(feedbackSlider);

    bypassedButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, bypassedId, bypassedButton);
    timeMsAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, timeMsId, timeMsSlider);
    feedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, feedbackId, feedbackSlider);
}

DelayComponent::~DelayComponent()
{
}

void DelayComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::wheat);

    auto localBounds = getLocalBounds();
    g.drawRoundedRectangle(localBounds.toFloat().reduced(5.0f), 5.0f, 2.0f);

    auto textBounds = juce::Rectangle<int>(localBounds.getWidth(), localBounds.getHeight() / 6);
    textBounds.setPosition(localBounds.getPosition());
    g.setFont(24.f);
    g.drawFittedText("Delay", textBounds, juce::Justification::centred, true);
}

void DelayComponent::resized()
{
    bypassedButton.setBounds(0, 0, 50, 50);
    timeMsSlider.setBounds(0, 50, 300, 30);
    feedbackSlider.setBounds(0, timeMsSlider.getBottom(), 300, 30);
}
