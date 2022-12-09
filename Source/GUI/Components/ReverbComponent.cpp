/*
  ==============================================================================

    ReverbComponent.cpp
    Metodos de ReverbComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbComponent.h"

//==============================================================================
ReverbComponent::ReverbComponent(juce::String title, juce::AudioProcessorValueTreeState& apvts, juce::String bypassedId, juce::String roomSizeId, juce::String widthId, juce::String dampingId, juce::String freezeModeId, juce::String dryLevelId, juce::String wetLevelId) :
    roomSizeSlider("Room size", "", false),
    widthSlider("Width", "", false),
    dampingSlider("Damping", "", false),
    freezeModeSlider("Freeze", "", false),
    dryLevelSlider("Dry level", "", false),
    wetLevelSlider("Wet level", "", false)
{
    this->title = title;

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
    g.setColour(juce::Colours::wheat);

    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    g.drawRoundedRectangle(localBounds, 5.0f, 2.0f);

    // Parte de arriba
    auto elementsBounds = localBounds.reduced(15);

    //auto distortionNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.85, elementsBounds.getHeight() * 0.2);
    auto elementsTopBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() * 0.2);
    //g.setColour(juce::Colours::wheat);
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
    auto sliderPadding = 12;

    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    auto elementsBounds = localBounds.reduced(15);

    auto reverbNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.85, elementsBounds.getHeight() * 0.2);

    auto bypassButtonBounds = juce::Rectangle<int>(reverbNameBounds.getRight(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.15, elementsBounds.getHeight() * 0.2);
    bypassedButton.setBounds(bypassButtonBounds);
    bypassedButton.setTopLeftPosition(juce::Point<int>(bypassButtonBounds.getCentre().getX(), bypassButtonBounds.getTopLeft().getY()));

    // Sliders
    auto roomSizeSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), bypassButtonBounds.getBottom() + (sliderPadding / 2), elementsBounds.getWidth(), (elementsBounds.getHeight() - bypassButtonBounds.getBottom()) / 5);
    roomSizeSlider.setBounds(roomSizeSliderBounds);

    auto widthSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), roomSizeSliderBounds.getBottom() + sliderPadding, elementsBounds.getWidth(), (elementsBounds.getHeight() - bypassButtonBounds.getBottom()) / 5);
    widthSlider.setBounds(widthSliderBounds);

    auto dampingSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), widthSliderBounds.getBottom() + sliderPadding, elementsBounds.getWidth(), (elementsBounds.getHeight() - bypassButtonBounds.getBottom()) / 5);
    dampingSlider.setBounds(dampingSliderBounds);

    auto freezeModeSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), dampingSliderBounds.getBottom() + sliderPadding, elementsBounds.getWidth(), (elementsBounds.getHeight() - bypassButtonBounds.getBottom()) / 5);
    freezeModeSlider.setBounds(freezeModeSliderBounds);

    auto dryLevelSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), freezeModeSliderBounds.getBottom() + sliderPadding, elementsBounds.getWidth(), (elementsBounds.getHeight() - bypassButtonBounds.getBottom()) / 5);
    dryLevelSlider.setBounds(dryLevelSliderBounds);

    auto wetLevelSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), dryLevelSliderBounds.getBottom() + sliderPadding, elementsBounds.getWidth(), (elementsBounds.getHeight() - bypassButtonBounds.getBottom()) / 5);
    wetLevelSlider.setBounds(wetLevelSliderBounds);
}
