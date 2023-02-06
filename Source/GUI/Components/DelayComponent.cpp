/*
  ==============================================================================

    DelayComponent.cpp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DelayComponent.h"

//==============================================================================
DelayComponent::DelayComponent(juce::String title, juce::Colour borderColour, juce::AudioProcessorValueTreeState& apvts, juce::String bypassedId, juce::String timeMsId, juce::String feedbackId) :
    timeMsSlider("Time", "ms", CustomSliderWithLabel::SliderStyle::Horizontal),
    feedbackSlider("Feedback", "", CustomSliderWithLabel::SliderStyle::Horizontal)
{
    this->title = title;
    delayBorderColour = borderColour;

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
    g.setColour(delayBorderColour);

    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    g.drawRoundedRectangle(localBounds, 5.0f, 2.0f);

    // Parte de arriba
    auto elementsBounds = localBounds.reduced(15);

    auto delayNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.85, elementsBounds.getHeight() * 0.2);
    //auto sliderPadding = 4;
    //slidersBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), delayNameBounds.getBottom() + sliderPadding, elementsBounds.getWidth(), elementsBounds.getHeight() * 0.8);

    auto elementsTopBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() * 0.2);
    g.setColour(ColorPalette::monwhite);
    g.setFont(24.f);
    g.drawFittedText(title, elementsTopBounds, juce::Justification::centred, true);

    auto compBypassed = bypassedButton.getToggleState();
    timeMsSlider.applyBypassedColorPalette(compBypassed);
    feedbackSlider.applyBypassedColorPalette(compBypassed);
}

void DelayComponent::resized()
{
    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    auto elementsBounds = localBounds.reduced(15);

    auto delayNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.85, elementsBounds.getHeight() * 0.2);

    auto bypassButtonBounds = juce::Rectangle<int>(delayNameBounds.getRight(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.15, elementsBounds.getHeight() * 0.2);
    bypassedButton.setBounds(bypassButtonBounds);
    bypassedButton.setTopLeftPosition(juce::Point<int>(bypassButtonBounds.getCentre().getX(), bypassButtonBounds.getTopLeft().getY()));

    // Sliders
    auto sliderPadding = 4;
    auto slidersBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), delayNameBounds.getBottom() + sliderPadding, elementsBounds.getWidth(), elementsBounds.getHeight() * 0.8);

    auto timeMsSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), slidersBounds.getPosition().getY(), slidersBounds.getWidth(), slidersBounds.getHeight()/ 2);
    timeMsSlider.setBounds(timeMsSliderBounds);

    auto feedbackSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), timeMsSliderBounds.getBottom(), slidersBounds.getWidth(), slidersBounds.getHeight() / 2);
    feedbackSlider.setBounds(feedbackSliderBounds);
}
