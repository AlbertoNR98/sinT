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
ChorusComponent::ChorusComponent(juce::String title, juce::Colour borderColour, juce::AudioProcessorValueTreeState& apvts, juce::String bypassedId, juce::String rateId, juce::String depthId, juce::String centreDelayId, juce::String feedbackId, juce::String mixId) : 
    rateSlider("Rate", "Hz", CustomSliderWithLabel::SliderStyle::Horizontal),
    depthSlider("Depth", "", CustomSliderWithLabel::SliderStyle::Horizontal),
    centreDelaySlider("Centre delay", "ms", CustomSliderWithLabel::SliderStyle::Horizontal),
    feedbackSlider("Feedback", "", CustomSliderWithLabel::SliderStyle::Horizontal),
    mixSlider("Mix", "", CustomSliderWithLabel::SliderStyle::Horizontal)
{
    this->title = title;
    chorusBorderColour = borderColour;

    addAndMakeVisible(bypassedButton);

    bypassedButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, bypassedId, bypassedButton);
    rateAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, rateId, rateSlider.getSlider());
    depthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, depthId, depthSlider.getSlider());
    centreDelayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, centreDelayId, centreDelaySlider.getSlider());
    feedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, feedbackId, feedbackSlider.getSlider());
    mixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, mixId, mixSlider.getSlider());

    auto compBypassed = bypassedButton.getToggleState();
    rateSlider.applyBypassedColorPalette(compBypassed);
    depthSlider.applyBypassedColorPalette(compBypassed);
    centreDelaySlider.applyBypassedColorPalette(compBypassed);
    feedbackSlider.applyBypassedColorPalette(compBypassed);
    mixSlider.applyBypassedColorPalette(compBypassed);

    addAndMakeVisible(rateSlider);
    addAndMakeVisible(depthSlider);
    addAndMakeVisible(centreDelaySlider);
    addAndMakeVisible(feedbackSlider);
    addAndMakeVisible(mixSlider);
}

ChorusComponent::~ChorusComponent()
{
}

void ChorusComponent::paint (juce::Graphics& g)
{
    g.setColour(chorusBorderColour);

    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    g.drawRoundedRectangle(localBounds, 5.0f, 2.0f);

    // Parte de arriba
    auto elementsBounds = localBounds.reduced(15);

    //auto distortionNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.85, elementsBounds.getHeight() * 0.2);
    auto elementsTopBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() * 0.15);
    g.setColour(ColorPalette::monwhite);
    g.setFont(24.f);
    g.drawFittedText(title, elementsTopBounds, juce::Justification::centred, true);

    auto compBypassed = bypassedButton.getToggleState();
    rateSlider.applyBypassedColorPalette(compBypassed);
    depthSlider.applyBypassedColorPalette(compBypassed);
    centreDelaySlider.applyBypassedColorPalette(compBypassed);
    feedbackSlider.applyBypassedColorPalette(compBypassed);
    mixSlider.applyBypassedColorPalette(compBypassed);
}

void ChorusComponent::resized()
{
    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    auto elementsBounds = localBounds.reduced(15);

    auto chorusNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.85, elementsBounds.getHeight() * 0.15);

    auto bypassButtonBounds = juce::Rectangle<int>(chorusNameBounds.getRight(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.15, elementsBounds.getHeight() * 0.15);
    bypassedButton.setBounds(bypassButtonBounds);
    bypassedButton.setTopLeftPosition(juce::Point<int>(bypassButtonBounds.getCentre().getX(), bypassButtonBounds.getTopLeft().getY()));

    // Sliders
    auto sliderPadding = 4;
    auto slidersBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), chorusNameBounds.getBottom() + sliderPadding, elementsBounds.getWidth(), elementsBounds.getHeight() * 0.85);

    auto rateSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), slidersBounds.getPosition().getY(), slidersBounds.getWidth(), slidersBounds.getHeight() / 5);
    rateSlider.setBounds(rateSliderBounds);

    auto depthSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), rateSliderBounds.getBottom(), slidersBounds.getWidth(), slidersBounds.getHeight() / 5);
    depthSlider.setBounds(depthSliderBounds);

    auto centreDelaySliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), depthSliderBounds.getBottom(), slidersBounds.getWidth(), slidersBounds.getHeight() / 5);
    centreDelaySlider.setBounds(centreDelaySliderBounds);

    auto feedbackSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), centreDelaySliderBounds.getBottom(), slidersBounds.getWidth(), slidersBounds.getHeight() / 5);
    feedbackSlider.setBounds(feedbackSliderBounds);

    auto mixSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), feedbackSliderBounds.getBottom(), slidersBounds.getWidth(), slidersBounds.getHeight() / 5);
    mixSlider.setBounds(mixSliderBounds);
}
