/*
  ==============================================================================

    ReverbComponent.cpp
    Metodos de ReverbComponent

  ==============================================================================
*/

#include "ReverbComponent.h"

//==============================================================================
ReverbComponent::ReverbComponent(juce::String title, juce::Colour borderColour, juce::AudioProcessorValueTreeState& apvts, juce::String bypassedId, juce::String roomSizeId, juce::String widthId, juce::String dampingId, juce::String freezeModeId, juce::String dryLevelId, juce::String wetLevelId) :
    freezeModeButton("Freeze"),
    roomSizeSlider("Room size", "", CustomSliderWithLabel::SliderStyle::Horizontal),
    widthSlider("Width", "", CustomSliderWithLabel::SliderStyle::Horizontal),
    dampingSlider("Damping", "", CustomSliderWithLabel::SliderStyle::Horizontal),
    dryLevelSlider("Dry level", "", CustomSliderWithLabel::SliderStyle::Horizontal),
    wetLevelSlider("Wet level", "", CustomSliderWithLabel::SliderStyle::Horizontal)
{
    this->title = title;
    reverbBorderColour = borderColour;

    addAndMakeVisible(bypassedButton);

    setupFreezeModeButton();
    addAndMakeVisible(freezeModeButton);

    bypassedButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, bypassedId, bypassedButton);
    freezeModeButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, freezeModeId, freezeModeButton);
    roomSizeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, roomSizeId, roomSizeSlider.getSlider());
    widthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, widthId, widthSlider.getSlider());
    dampingAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, dampingId, dampingSlider.getSlider());
    dryLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, dryLevelId, dryLevelSlider.getSlider());
    wetLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, wetLevelId, wetLevelSlider.getSlider());

    auto compBypassed = bypassedButton.getToggleState();
    setupFreezeModeButton(compBypassed);
    roomSizeSlider.applyBypassedColorPalette(compBypassed);
    widthSlider.applyBypassedColorPalette(compBypassed);
    dampingSlider.applyBypassedColorPalette(compBypassed);
    dryLevelSlider.applyBypassedColorPalette(compBypassed);
    wetLevelSlider.applyBypassedColorPalette(compBypassed);

    addAndMakeVisible(roomSizeSlider);
    addAndMakeVisible(widthSlider);
    addAndMakeVisible(dampingSlider);
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
    g.drawRoundedRectangle(localBounds, 6.0f, 3.5f);

    // Parte de arriba
    const auto boundsPadding = 16;
    auto elementsBounds = localBounds.reduced(boundsPadding);

    auto elementsTopBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() * 0.15);
    g.setColour(ColorPalette::monwhite);
    drawTitle(g, title, elementsTopBounds, juce::Justification::centred, 28.f, 0.85f);

    auto compBypassed = bypassedButton.getToggleState();
    setupFreezeModeButton(compBypassed);
    roomSizeSlider.applyBypassedColorPalette(compBypassed);
    widthSlider.applyBypassedColorPalette(compBypassed);
    dampingSlider.applyBypassedColorPalette(compBypassed);
    dryLevelSlider.applyBypassedColorPalette(compBypassed);
    wetLevelSlider.applyBypassedColorPalette(compBypassed);
}

void ReverbComponent::resized()
{
    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    const auto boundsPadding = 16;
    auto elementsBounds = localBounds.reduced(boundsPadding);
    auto elementsTopBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() * 0.15);

    const auto freezeButtonPadding = elementsTopBounds.getWidth() * 0.05;
    auto freezeModeButtonBounds = juce::Rectangle<int>(elementsTopBounds.getPosition().getX() + freezeButtonPadding, elementsTopBounds.getPosition().getY(), elementsTopBounds.getWidth() * 0.2, elementsTopBounds.getHeight());

    auto reverbNameBounds = juce::Rectangle<int>(freezeModeButtonBounds.getRight() + freezeButtonPadding, elementsTopBounds.getPosition().getY(), elementsTopBounds.getWidth() * 0.6, elementsTopBounds.getHeight());
    auto bypassButtonBounds = juce::Rectangle<int>(reverbNameBounds.getRight(), elementsTopBounds.getPosition().getY(), elementsTopBounds.getWidth() * 0.1, elementsTopBounds.getHeight());
    
    bypassedButton.setBounds(bypassButtonBounds.withSizeKeepingCentre(bypassButtonBounds.getWidth(), bypassButtonBounds.getHeight() * 0.7));
    freezeModeButton.setBounds(freezeModeButtonBounds);

    // Sliders
    const auto sliderPadding = 4;
    auto slidersBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsTopBounds.getBottom() + sliderPadding, elementsBounds.getWidth(), elementsBounds.getHeight() * 0.85);

    auto roomSizeSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), slidersBounds.getPosition().getY(), slidersBounds.getWidth(), slidersBounds.getHeight() / 5);
    roomSizeSlider.setBounds(roomSizeSliderBounds);

    auto widthSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), roomSizeSliderBounds.getBottom(), slidersBounds.getWidth(), slidersBounds.getHeight() / 5);
    widthSlider.setBounds(widthSliderBounds);

    auto dampingSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), widthSliderBounds.getBottom(), slidersBounds.getWidth(), slidersBounds.getHeight() / 5);
    dampingSlider.setBounds(dampingSliderBounds);

    auto dryLevelSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), dampingSliderBounds.getBottom(), slidersBounds.getWidth(), slidersBounds.getHeight() / 5);
    dryLevelSlider.setBounds(dryLevelSliderBounds);

    auto wetLevelSliderBounds = juce::Rectangle<int>(slidersBounds.getPosition().getX(), dryLevelSliderBounds.getBottom(), slidersBounds.getWidth(), slidersBounds.getHeight() / 5);
    wetLevelSlider.setBounds(wetLevelSliderBounds);
}

void ReverbComponent::setupFreezeModeButton(bool bypassed)
{
    freezeModeButton.setClickingTogglesState(true);

    if (bypassed)
    {
        freezeModeButton.setColour(juce::ComboBox::outlineColourId, ColorPalette::bypassgrey);

        freezeModeButton.setColour(juce::TextButton::buttonColourId, ColorPalette::transparentblack);
        freezeModeButton.setColour(juce::TextButton::textColourOffId, ColorPalette::bypassgrey);

        freezeModeButton.setColour(juce::TextButton::buttonOnColourId, ColorPalette::bypassgrey);
        freezeModeButton.setColour(juce::TextButton::textColourOnId, ColorPalette::bypassgrey);
    }
    else
    {
        freezeModeButton.setColour(juce::ComboBox::outlineColourId, ColorPalette::monwhite);

        freezeModeButton.setColour(juce::TextButton::buttonColourId, ColorPalette::transparentblack);
        freezeModeButton.setColour(juce::TextButton::textColourOffId, ColorPalette::monwhite);

        freezeModeButton.setColour(juce::TextButton::buttonOnColourId, ColorPalette::betis);
        freezeModeButton.setColour(juce::TextButton::textColourOnId, ColorPalette::monwhite);
    }
}
