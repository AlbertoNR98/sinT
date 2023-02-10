/*
  ==============================================================================

    ReverbComponent.cpp
    Metodos de ReverbComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbComponent.h"

//==============================================================================
ReverbComponent::ReverbComponent(juce::String title, juce::Colour borderColour, juce::AudioProcessorValueTreeState& apvts, juce::String bypassedId, juce::String roomSizeId, juce::String widthId, juce::String dampingId, juce::String freezeModeId, juce::String dryLevelId, juce::String wetLevelId) :
    roomSizeSlider("Room size", "", CustomSliderWithLabel::SliderStyle::Horizontal),
    widthSlider("Width", "", CustomSliderWithLabel::SliderStyle::Horizontal),
    dampingSlider("Damping", "", CustomSliderWithLabel::SliderStyle::Horizontal),
    freezeModeSlider("Freeze", "", CustomSliderWithLabel::SliderStyle::Horizontal),
    dryLevelSlider("Dry level", "", CustomSliderWithLabel::SliderStyle::Horizontal),
    wetLevelSlider("Wet level", "", CustomSliderWithLabel::SliderStyle::Horizontal)
{
    this->title = title;
    reverbBorderColour = borderColour;

    addAndMakeVisible(bypassedButton);

    bypassedButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, bypassedId, bypassedButton);
    roomSizeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, roomSizeId, roomSizeSlider.getSlider());
    widthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, widthId, widthSlider.getSlider());
    dampingAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, dampingId, dampingSlider.getSlider());
    freezeModeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, freezeModeId, freezeModeSlider.getSlider());
    dryLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, dryLevelId, dryLevelSlider.getSlider());
    wetLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, wetLevelId, wetLevelSlider.getSlider());

    auto compBypassed = bypassedButton.getToggleState();
    roomSizeSlider.applyBypassedColorPalette(compBypassed);
    widthSlider.applyBypassedColorPalette(compBypassed);
    dampingSlider.applyBypassedColorPalette(compBypassed);
    freezeModeSlider.applyBypassedColorPalette(compBypassed);
    dryLevelSlider.applyBypassedColorPalette(compBypassed);
    wetLevelSlider.applyBypassedColorPalette(compBypassed);

    addAndMakeVisible(roomSizeSlider);
    addAndMakeVisible(widthSlider);
    addAndMakeVisible(dampingSlider);
    addAndMakeVisible(freezeModeSlider);
    addAndMakeVisible(dryLevelSlider);
    addAndMakeVisible(wetLevelSlider);
}

ReverbComponent::~ReverbComponent()
{
}

void ReverbComponent::paint (juce::Graphics& g)
{
    g.setColour(reverbBorderColour);

    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    g.drawRoundedRectangle(localBounds, 5.0f, 2.0f);

    // Parte de arriba
    const auto boundsPadding = 16;
    auto elementsBounds = localBounds.reduced(boundsPadding);

    //auto reverbNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.85, elementsBounds.getHeight() * 0.2);
    auto elementsTopBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() * 0.15);
    g.setColour(ColorPalette::monwhite);
    g.setFont(28.f);
    g.drawFittedText(title, elementsTopBounds, juce::Justification::centred, true);

    auto compBypassed = bypassedButton.getToggleState();
    roomSizeSlider.applyBypassedColorPalette(compBypassed);
    widthSlider.applyBypassedColorPalette(compBypassed);
    dampingSlider.applyBypassedColorPalette(compBypassed);
    freezeModeSlider.applyBypassedColorPalette(compBypassed);
    dryLevelSlider.applyBypassedColorPalette(compBypassed);
    wetLevelSlider.applyBypassedColorPalette(compBypassed);
}

void ReverbComponent::resized()
{
    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    const auto boundsPadding = 16;
    auto elementsBounds = localBounds.reduced(boundsPadding);
    auto elementsTopBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() * 0.15);

    auto reverbNameBounds = juce::Rectangle<int>(elementsTopBounds.getPosition().getX(), elementsTopBounds.getPosition().getY(), elementsTopBounds.getWidth() * 0.9, elementsTopBounds.getHeight());
    auto bypassButtonBounds = juce::Rectangle<int>(reverbNameBounds.getRight(), elementsTopBounds.getPosition().getY(), elementsTopBounds.getWidth() * 0.1, elementsTopBounds.getHeight());
    bypassedButton.setBounds(bypassButtonBounds.withSizeKeepingCentre(bypassButtonBounds.getWidth(), bypassButtonBounds.getHeight() * 0.7));

    // Sliders
    auto sliderPadding = 4;
    auto slidersBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsTopBounds.getBottom() + sliderPadding, elementsBounds.getWidth(), elementsBounds.getHeight() * 0.85);

    auto roomSizeSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), slidersBounds.getPosition().getY(), slidersBounds.getWidth(), slidersBounds.getHeight() / 6);
    roomSizeSlider.setBounds(roomSizeSliderBounds);

    auto widthSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), roomSizeSliderBounds.getBottom(), slidersBounds.getWidth(), slidersBounds.getHeight() / 6);
    widthSlider.setBounds(widthSliderBounds);

    auto dampingSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), widthSliderBounds.getBottom(), slidersBounds.getWidth(), slidersBounds.getHeight() / 6);
    dampingSlider.setBounds(dampingSliderBounds);

    auto freezeModeSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), dampingSliderBounds.getBottom(), slidersBounds.getWidth(), slidersBounds.getHeight() / 6);
    freezeModeSlider.setBounds(freezeModeSliderBounds);

    auto dryLevelSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), freezeModeSliderBounds.getBottom(), slidersBounds.getWidth(), slidersBounds.getHeight() / 6);
    dryLevelSlider.setBounds(dryLevelSliderBounds);

    auto wetLevelSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), dryLevelSliderBounds.getBottom(), slidersBounds.getWidth(), slidersBounds.getHeight() / 6);
    wetLevelSlider.setBounds(wetLevelSliderBounds);

    /*
    auto sliderPadding = 0;

    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    auto elementsBounds = localBounds.reduced(15);

    auto reverbNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.85, elementsBounds.getHeight() * 0.2);

    auto bypassButtonBounds = juce::Rectangle<int>(reverbNameBounds.getRight(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.15, elementsBounds.getHeight() * 0.2);
    bypassedButton.setBounds(bypassButtonBounds);
    bypassedButton.setTopLeftPosition(juce::Point<int>(bypassButtonBounds.getCentre().getX(), bypassButtonBounds.getTopLeft().getY()));

    // Sliders
    auto roomSizeSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), bypassButtonBounds.getBottom() + sliderPadding, elementsBounds.getWidth(), (elementsBounds.getHeight() - bypassButtonBounds.getBottom()) / 5);
    roomSizeSlider.setBounds(roomSizeSliderBounds);

    auto widthSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), roomSizeSliderBounds.getBottom() + (sliderPadding * 0.5), elementsBounds.getWidth(), (elementsBounds.getHeight() - bypassButtonBounds.getBottom()) / 5);
    widthSlider.setBounds(widthSliderBounds);

    auto dampingSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), widthSliderBounds.getBottom() + (sliderPadding * 0.5), elementsBounds.getWidth(), (elementsBounds.getHeight() - bypassButtonBounds.getBottom()) / 5);
    dampingSlider.setBounds(dampingSliderBounds);

    auto freezeModeSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), dampingSliderBounds.getBottom() + (sliderPadding * 0.5), elementsBounds.getWidth(), (elementsBounds.getHeight() - bypassButtonBounds.getBottom()) / 5);
    freezeModeSlider.setBounds(freezeModeSliderBounds);

    auto dryLevelSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), freezeModeSliderBounds.getBottom() + (sliderPadding * 0.5), elementsBounds.getWidth(), (elementsBounds.getHeight() - bypassButtonBounds.getBottom()) / 5);
    dryLevelSlider.setBounds(dryLevelSliderBounds);

    auto wetLevelSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), dryLevelSliderBounds.getBottom() + (sliderPadding * 0.5), elementsBounds.getWidth(), (elementsBounds.getHeight() - bypassButtonBounds.getBottom()) / 5);
    wetLevelSlider.setBounds(wetLevelSliderBounds);
    */
}
