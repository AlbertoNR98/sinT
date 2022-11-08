/*
  ==============================================================================

    ChorusComponent.cpp
    Created: 6 Sep 2022 11:43:47am
    Author:  Alberto Naranjo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChorusComponent.h"

//==============================================================================
ChorusComponent::ChorusComponent(juce::AudioProcessorValueTreeState& apvts, juce::String bypassedId, juce::String rateId, juce::String depthId, juce::String centreDelayId, juce::String feedbackId, juce::String mixId)
{
    addAndMakeVisible(bypassedButton);

    rateSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(rateSlider);

    depthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(depthSlider);

    centreDelaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(centreDelaySlider);

    feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(feedbackSlider);

    mixSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(mixSlider);


    bypassedButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, rateId, bypassedButton);
    rateAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, rateId, rateSlider);
    depthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, depthId, depthSlider);
    centreDelayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, centreDelayId, centreDelaySlider);
    feedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, feedbackId, feedbackSlider);
    mixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, mixId, mixSlider);
}

ChorusComponent::~ChorusComponent()
{
}

void ChorusComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::wheat);

    auto localBounds = getLocalBounds();
    g.drawRoundedRectangle(localBounds.toFloat().reduced(5.0f), 5.0f, 2.0f);

    auto textBounds = juce::Rectangle<int>(localBounds.getWidth(), localBounds.getHeight() / 6);
    textBounds.setPosition(localBounds.getPosition());
    g.setFont(24.f);
    g.drawFittedText("Chorus", textBounds, juce::Justification::centred, true);
}

void ChorusComponent::resized()
{
    bypassedButton.setBounds(0, 0, 50, 50);
    rateSlider.setBounds(0, 50, 300, 30);
    depthSlider.setBounds(0, rateSlider.getBottom(), 300, 30);
    centreDelaySlider.setBounds(0, depthSlider.getBottom(), 300, 30);
    feedbackSlider.setBounds(0, centreDelaySlider.getBottom(), 300, 30);
    mixSlider.setBounds(0, feedbackSlider.getBottom(), 300, 30);
}
