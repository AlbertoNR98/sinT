/*
  ==============================================================================

    DistortionComponent.cpp
    Metodos de DistortionComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DistortionComponent.h"

//==============================================================================
DistortionComponent::DistortionComponent(juce::String title, juce::AudioProcessorValueTreeState& apvts, juce::String bypassedId, juce::String driveId, juce::String rangeId, juce::String blendId) :
    driveSlider("Drive", "", CustomSliderWithLabel::SliderStyle::Horizontal),
    rangeSlider("Range", "", CustomSliderWithLabel::SliderStyle::Horizontal),
    blendSlider("Blend", "", CustomSliderWithLabel::SliderStyle::Horizontal)
{
    this->title = title;

    addAndMakeVisible(bypassedButton);

    distortionBypassedButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, bypassedId, bypassedButton);
    driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, driveId, driveSlider.getSlider());
    rangeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, rangeId, rangeSlider.getSlider());
    blendAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, blendId, blendSlider.getSlider());

    auto compBypassed = bypassedButton.getToggleState();
    driveSlider.applyBypassedColorPalette(compBypassed);
    rangeSlider.applyBypassedColorPalette(compBypassed);
    blendSlider.applyBypassedColorPalette(compBypassed);

    addAndMakeVisible(driveSlider);
    addAndMakeVisible(rangeSlider);
    addAndMakeVisible(blendSlider);
}

DistortionComponent::~DistortionComponent()
{
}

void DistortionComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::wheat);

    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    g.drawRoundedRectangle(localBounds, 5.0f, 2.0f);

    // Parte de arriba
    auto elementsBounds = localBounds.reduced(15);

    //g.setColour(juce::Colours::orangered);
    auto distortionNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.85, elementsBounds.getHeight() * 0.2);
    //g.drawRect(distortionNameBounds);

    //auto sliderPadding = 4;
    // slidersBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), distortionNameBounds.getBottom() + sliderPadding, elementsBounds.getWidth(), elementsBounds.getHeight() * 0.8);
    //g.drawRect(slidersBounds);
    //g.drawRect(elementsBounds);

    auto elementsTopBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() * 0.2); 
    //g.setColour(juce::Colours::wheat);
    g.setFont(24.f);
    g.drawFittedText(title, elementsTopBounds, juce::Justification::centred, true);
    //g.drawRect(elementsTopBounds);

    auto compBypassed = bypassedButton.getToggleState();
    driveSlider.applyBypassedColorPalette(compBypassed);
    rangeSlider.applyBypassedColorPalette(compBypassed);
    blendSlider.applyBypassedColorPalette(compBypassed);
}

void DistortionComponent::resized()
{
    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    auto elementsBounds = localBounds.reduced(15);

    auto distortionNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.85, elementsBounds.getHeight() * 0.2);

    auto bypassButtonBounds = juce::Rectangle<int>(distortionNameBounds.getRight(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.15, elementsBounds.getHeight() * 0.2);
    bypassedButton.setBounds(bypassButtonBounds);
    bypassedButton.setTopLeftPosition(juce::Point<int>(bypassButtonBounds.getCentre().getX(), bypassButtonBounds.getTopLeft().getY()));

    // Sliders
    auto sliderPadding = 4;
    auto slidersBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), distortionNameBounds.getBottom() + sliderPadding, elementsBounds.getWidth(), elementsBounds.getHeight() * 0.8);

    auto driveSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), slidersBounds.getPosition().getY(), slidersBounds.getWidth(), slidersBounds.getHeight() / 3);
    driveSlider.setBounds(driveSliderBounds);

    auto rangeSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), driveSliderBounds.getBottom(), slidersBounds.getWidth(), slidersBounds.getHeight()/ 3);
    rangeSlider.setBounds(rangeSliderBounds);

    auto blendSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), rangeSliderBounds.getBottom(), slidersBounds.getWidth(), slidersBounds.getHeight() / 3);
    blendSlider.setBounds(blendSliderBounds);
}
