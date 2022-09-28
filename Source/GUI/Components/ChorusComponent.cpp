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
ChorusComponent::ChorusComponent(juce::AudioProcessorValueTreeState& apvts, juce::String rateId, juce::String depthId, juce::String centreDelayId, juce::String feedbackId, juce::String mixId)
{
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
    g.fillAll(juce::Colours::black);
}

void ChorusComponent::resized()
{
    rateSlider.setBounds(0, 0, 300, 30);
    depthSlider.setBounds(0, rateSlider.getBottom(), 300, 30);
    centreDelaySlider.setBounds(0, depthSlider.getBottom(), 300, 30);
    feedbackSlider.setBounds(0, centreDelaySlider.getBottom(), 300, 30);
    mixSlider.setBounds(0, feedbackSlider.getBottom(), 300, 30);
}
