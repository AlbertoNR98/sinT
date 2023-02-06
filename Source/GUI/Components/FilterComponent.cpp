/*
  ==============================================================================

    FilterComponent.cpp
    Metodos de FilterComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::Colour borderColour, juce::String filterBypassedId, juce::String filterModeSelectorId, juce::String filterCutoffFreqId, juce::String filterResonanceId) :
    filterCutoffFreqSlider("Cutoff", "Hz"),
    filterResonanceSlider("Resonance")
{
    filterBorderColour = borderColour;
    addAndMakeVisible(filterBypassedButton);

    juce::StringArray waveOptions{ "LPF", "BPF", "HPF" };
    filterModeSelector.addItemList(waveOptions, 1);
    filterModeSelector.setJustificationType(juce::Justification::centred);
    filterModeSelector.setColour(juce::ComboBox::ColourIds::backgroundColourId, ColorPalette::darkgray);
    addAndMakeVisible(filterModeSelector);

    filterBypassedButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, filterBypassedId, filterBypassedButton);
    filterModeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filterModeSelectorId, filterModeSelector);
    filterCutoffFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, filterCutoffFreqId, filterCutoffFreqSlider.getSlider());
    filterResonanceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, filterResonanceId, filterResonanceSlider.getSlider());

    auto compBypassed = filterBypassedButton.getToggleState();
    filterCutoffFreqSlider.applyBypassedColorPalette(compBypassed);
    filterResonanceSlider.applyBypassedColorPalette(compBypassed);

    addAndMakeVisible(filterCutoffFreqSlider);
    addAndMakeVisible(filterResonanceSlider);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    g.setColour(filterBorderColour);

    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    g.drawRoundedRectangle(localBounds, 5.0f, 2.0f);

    // Parte de arriba
    auto elementsBounds = localBounds.reduced(15);

    auto filterNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.55, elementsBounds.getHeight() * 0.2);
    g.setColour(ColorPalette::monwhite);
    g.setFont(28.f);
    g.drawFittedText(filterTitle, filterNameBounds, juce::Justification::centredLeft, true);

    auto filterModeSelectorBoundsWithoutPadding = juce::Rectangle<int>(filterNameBounds.getRight(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.3, elementsBounds.getHeight() * 0.2);

    auto paddingFilterModeSelector = 15;
    auto filterModeSelectorBounds = juce::Rectangle<int>(filterNameBounds.getRight(), elementsBounds.getPosition().getY() + paddingFilterModeSelector, elementsBounds.getWidth() * 0.3, (elementsBounds.getHeight() * 0.2) - (2 * paddingFilterModeSelector));

    auto bypassButtonBounds = juce::Rectangle<int>(filterModeSelectorBounds.getRight(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.15, elementsBounds.getHeight() * 0.2);

    /*
    // Sliders -> Para debug
    auto filterCutoffFreqSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), bypassButtonBounds.getBottom(), elementsBounds.getWidth() * 0.5, elementsBounds.getHeight() * 0.8);
    auto filterResonanceSliderBounds = juce::Rectangle<int>(filterCutoffFreqSliderBounds.getRight(), bypassButtonBounds.getBottom(), elementsBounds.getWidth() * 0.5, elementsBounds.getHeight() * 0.8);
    */

    auto compBypassed = filterBypassedButton.getToggleState();
    filterCutoffFreqSlider.applyBypassedColorPalette(compBypassed);
    filterResonanceSlider.applyBypassedColorPalette(compBypassed);
}

void FilterComponent::resized()
{
    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    auto elementsBounds = localBounds.reduced(15);

    auto filterNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.55, elementsBounds.getHeight() * 0.2);

    auto paddingFilterModeSelector = 15;
    auto filterModeSelectorBounds = juce::Rectangle<int>(filterNameBounds.getRight(), elementsBounds.getPosition().getY() + paddingFilterModeSelector, elementsBounds.getWidth() * 0.3, (elementsBounds.getHeight() * 0.2) - (2 * paddingFilterModeSelector));
    filterModeSelector.setBounds(filterModeSelectorBounds);

    auto bypassButtonBounds = juce::Rectangle<int>(filterModeSelectorBounds.getRight(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.15, elementsBounds.getHeight() * 0.2);
    filterBypassedButton.setBounds(bypassButtonBounds);
    filterBypassedButton.setTopLeftPosition(juce::Point<int>(bypassButtonBounds.getCentre().getX(), bypassButtonBounds.getTopLeft().getY()));

    // Sliders
    auto filterCutoffFreqSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), bypassButtonBounds.getBottom(), elementsBounds.getWidth() * 0.5, elementsBounds.getHeight() * 0.8);
    filterCutoffFreqSlider.setBounds(filterCutoffFreqSliderBounds);

    auto filterResonanceSliderBounds = juce::Rectangle<int>(filterCutoffFreqSliderBounds.getRight(), bypassButtonBounds.getBottom(), elementsBounds.getWidth() * 0.5, elementsBounds.getHeight() * 0.8);
    filterResonanceSlider.setBounds(filterResonanceSliderBounds);
}
