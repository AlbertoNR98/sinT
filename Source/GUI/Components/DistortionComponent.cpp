/*
  ==============================================================================

    DistortionComponent.cpp
    Metodos de DistortionComponent

  ==============================================================================
*/

#include "DistortionComponent.h"

//==============================================================================
DistortionComponent::DistortionComponent(juce::String title, juce::Colour borderColour, juce::AudioProcessorValueTreeState& apvts, juce::String bypassedId, juce::String driveId, juce::String rangeId, juce::String mixId) :
    driveSlider("Drive", "", CustomSliderWithLabel::SliderStyle::Horizontal),
    rangeSlider("Range", "", CustomSliderWithLabel::SliderStyle::Horizontal),
    mixSlider("Mix", "", CustomSliderWithLabel::SliderStyle::Horizontal)
{
    this->title = title;
    distortionBorderColour = borderColour;

    addAndMakeVisible(bypassedButton);

    distortionBypassedButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, bypassedId, bypassedButton);
    driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, driveId, driveSlider.getSlider());
    rangeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, rangeId, rangeSlider.getSlider());
    mixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, mixId, mixSlider.getSlider());

    auto compBypassed = bypassedButton.getToggleState();
    driveSlider.applyBypassedColorPalette(compBypassed);
    rangeSlider.applyBypassedColorPalette(compBypassed);
    mixSlider.applyBypassedColorPalette(compBypassed);

    addAndMakeVisible(driveSlider);
    addAndMakeVisible(rangeSlider);
    addAndMakeVisible(mixSlider);
}

DistortionComponent::~DistortionComponent()
{
}

void DistortionComponent::paint (juce::Graphics& g)
{
    g.setColour(distortionBorderColour);

    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    g.drawRoundedRectangle(localBounds, 6.0f, 3.5f);

    // Parte de arriba
    const auto boundsPadding = 16;
    auto elementsBounds = localBounds.reduced(boundsPadding);

    auto elementsTopBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() * 0.2); 
    g.setColour(ColorPalette::monwhite);
    drawTitle(g, title, elementsTopBounds, juce::Justification::centred, 26.f, 1.f);
  
    auto compBypassed = bypassedButton.getToggleState();
    driveSlider.applyBypassedColorPalette(compBypassed);
    rangeSlider.applyBypassedColorPalette(compBypassed);
    mixSlider.applyBypassedColorPalette(compBypassed);
}

void DistortionComponent::resized()
{
    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    const auto boundsPadding = 16;
    auto elementsBounds = localBounds.reduced(boundsPadding);
    auto elementsTopBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() * 0.2);
    
    auto distortionNameBounds = juce::Rectangle<int>(elementsTopBounds.getPosition().getX(), elementsTopBounds.getPosition().getY(), elementsTopBounds.getWidth() * 0.9, elementsTopBounds.getHeight());
    auto bypassButtonBounds = juce::Rectangle<int>(distortionNameBounds.getRight(), elementsTopBounds.getPosition().getY(), elementsTopBounds.getWidth() * 0.1, elementsTopBounds.getHeight());
    bypassedButton.setBounds(bypassButtonBounds);

    // Sliders
    const auto sliderPadding = 4;
    auto slidersBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsTopBounds.getBottom() + sliderPadding, elementsBounds.getWidth(), elementsBounds.getHeight() * 0.8);

    auto driveSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), slidersBounds.getPosition().getY(), slidersBounds.getWidth(), slidersBounds.getHeight() / 3);
    driveSlider.setBounds(driveSliderBounds);

    auto rangeSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), driveSliderBounds.getBottom(), slidersBounds.getWidth(), slidersBounds.getHeight()/ 3);
    rangeSlider.setBounds(rangeSliderBounds);

    auto mixSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), rangeSliderBounds.getBottom(), slidersBounds.getWidth(), slidersBounds.getHeight() / 3);
    mixSlider.setBounds(mixSliderBounds);
}
