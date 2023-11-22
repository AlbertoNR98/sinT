/*
  ==============================================================================

    DelayComponent.cpp
    Metodos de DelayComponent

  ==============================================================================
*/

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
    g.drawRoundedRectangle(localBounds, 6.0f, 3.5f);

    // Parte de arriba
    const auto boundsPadding = 16;
    auto elementsBounds = localBounds.reduced(boundsPadding);

    auto elementsTopBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() * 0.2);
    g.setColour(ColorPalette::monwhite);
    drawTitle(g, title, elementsTopBounds, juce::Justification::centred, 26.f, 1.f);

    auto compBypassed = bypassedButton.getToggleState();
    timeMsSlider.applyBypassedColorPalette(compBypassed);
    feedbackSlider.applyBypassedColorPalette(compBypassed);
}

void DelayComponent::resized()
{
    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    const auto boundsPadding = 16;
    auto elementsBounds = localBounds.reduced(boundsPadding);
    auto elementsTopBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() * 0.2);

    auto delayNameBounds = juce::Rectangle<int>(elementsTopBounds.getPosition().getX(), elementsTopBounds.getPosition().getY(), elementsTopBounds.getWidth() * 0.9, elementsTopBounds.getHeight());
    auto bypassButtonBounds = juce::Rectangle<int>(delayNameBounds.getRight(), elementsTopBounds.getPosition().getY(), elementsTopBounds.getWidth() * 0.1, elementsTopBounds.getHeight());
    bypassedButton.setBounds(bypassButtonBounds);

    // Sliders
    const auto sliderPadding = 4;
    auto slidersBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsTopBounds.getBottom() + sliderPadding, elementsBounds.getWidth(), elementsBounds.getHeight() * 0.8);

    auto timeMsSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), slidersBounds.getPosition().getY(), slidersBounds.getWidth(), slidersBounds.getHeight()/ 2);
    timeMsSlider.setBounds(timeMsSliderBounds);

    auto feedbackSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), timeMsSliderBounds.getBottom(), slidersBounds.getWidth(), slidersBounds.getHeight() / 2);
    feedbackSlider.setBounds(feedbackSliderBounds);
}
