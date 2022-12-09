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
DelayComponent::DelayComponent(juce::String title, juce::AudioProcessorValueTreeState& apvts, juce::String bypassedId, juce::String timeMsId, juce::String feedbackId) :
    timeMsSlider("Time", "ms", false),
    feedbackSlider("Feedback", "", false)
{
    this->title = title;

    addAndMakeVisible(bypassedButton);

    bypassedButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, bypassedId, bypassedButton);
    timeMsAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, timeMsId, timeMsSlider.getSlider());
    feedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, feedbackId, feedbackSlider.getSlider());

    auto compBypassed = bypassedButton.getToggleState();
    timeMsSlider.applyBypassedColorPalette(compBypassed);
    feedbackSlider.applyBypassedColorPalette(compBypassed);

    addAndMakeVisible(timeMsSlider);
    addAndMakeVisible(feedbackSlider);
}

DelayComponent::~DelayComponent()
{
}

void DelayComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::wheat);

    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    g.drawRoundedRectangle(localBounds, 5.0f, 2.0f);

    // Parte de arriba
    auto elementsBounds = localBounds.reduced(15);

    auto elementsTopBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() * 0.2);
    //g.setColour(juce::Colours::wheat);
    g.setFont(28.f);
    g.drawFittedText(title, elementsTopBounds, juce::Justification::centred, true);

    auto compBypassed = bypassedButton.getToggleState();
    timeMsSlider.applyBypassedColorPalette(compBypassed);
    feedbackSlider.applyBypassedColorPalette(compBypassed);
}

void DelayComponent::resized()
{
    auto sliderPadding = 12;

    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    auto elementsBounds = localBounds.reduced(15);

    auto delayNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.85, elementsBounds.getHeight() * 0.2);

    auto bypassButtonBounds = juce::Rectangle<int>(delayNameBounds.getRight(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.15, elementsBounds.getHeight() * 0.2);
    bypassedButton.setBounds(bypassButtonBounds);
    bypassedButton.setTopLeftPosition(juce::Point<int>(bypassButtonBounds.getCentre().getX(), bypassButtonBounds.getTopLeft().getY()));

    // Sliders
    auto timeMsSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), bypassButtonBounds.getBottom() + (sliderPadding / 2), elementsBounds.getWidth(), (elementsBounds.getHeight() - bypassButtonBounds.getBottom()) / 2);
    timeMsSlider.setBounds(timeMsSliderBounds);

    auto feedbackSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), timeMsSliderBounds.getBottom() + sliderPadding, elementsBounds.getWidth(), (elementsBounds.getHeight() - bypassButtonBounds.getBottom()) / 2);
    feedbackSlider.setBounds(feedbackSliderBounds);
}
