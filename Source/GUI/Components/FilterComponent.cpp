/*
  ==============================================================================

    FilterComponent.cpp
    FilterComponent methods

  ==============================================================================
*/

#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::Colour borderColour, juce::String filterBypassedId, juce::String filterModeSelectorId, juce::String filterCutoffFreqId, juce::String filterResonanceId) :
    filterCutoffFreqSlider("Cutoff", "Hz"),
    filterResonanceSlider("Resonance")
{
    filterBorderColour = borderColour;
    addAndMakeVisible(filterBypassedButton);

    juce::StringArray filterModes{ "LPF", "BPF", "HPF" };
    filterModeSelector.addItemList(filterModes, 1);
    filterModeSelector.setJustificationType(juce::Justification::centred);

    filterBypassedButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, filterBypassedId, filterBypassedButton);
    filterModeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filterModeSelectorId, filterModeSelector);
    filterCutoffFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, filterCutoffFreqId, filterCutoffFreqSlider.getSlider());
    filterResonanceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, filterResonanceId, filterResonanceSlider.getSlider());

    auto compBypassed = filterBypassedButton.getToggleState();
    setupFilterModeSelector(compBypassed);
    filterCutoffFreqSlider.applyBypassedColorPalette(compBypassed);
    filterResonanceSlider.applyBypassedColorPalette(compBypassed);

    addAndMakeVisible(filterModeSelector);
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

    // Top section
    const auto boundsPadding = 16;
    auto elementsBounds = localBounds.reduced(boundsPadding);

    auto filterNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.55, elementsBounds.getHeight() * 0.2);
    g.setColour(ColorPalette::monwhite);
    g.setFont(28.f);
    g.drawFittedText(filterTitle, filterNameBounds, juce::Justification::centred, true);

    auto compBypassed = filterBypassedButton.getToggleState();
    setupFilterModeSelector(compBypassed);
    filterCutoffFreqSlider.applyBypassedColorPalette(compBypassed);
    filterResonanceSlider.applyBypassedColorPalette(compBypassed);
}

void FilterComponent::resized()
{
    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    const auto boundsPadding = 16;
    auto elementsBounds = localBounds.reduced(boundsPadding);

    auto filterNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.55, elementsBounds.getHeight() * 0.2);

    auto paddingFilterModeSelector = 15;
    auto filterModeSelectorBounds = juce::Rectangle<int>(filterNameBounds.getRight() + paddingFilterModeSelector, elementsBounds.getPosition().getY() + paddingFilterModeSelector, elementsBounds.getWidth() * 0.25, (elementsBounds.getHeight() * 0.2) - (paddingFilterModeSelector * 2));
    filterModeSelector.setBounds(filterModeSelectorBounds);

    auto bypassButtonBounds = juce::Rectangle<int>(filterModeSelectorBounds.getRight() + paddingFilterModeSelector + (boundsPadding * 0.5), elementsBounds.getPosition().getY(), (elementsBounds.getWidth() * 0.2) - (paddingFilterModeSelector * 2) - (boundsPadding * 0.5), elementsBounds.getHeight() * 0.2);
    filterBypassedButton.setBounds(bypassButtonBounds.withSizeKeepingCentre(bypassButtonBounds.getWidth(), bypassButtonBounds.getHeight() * 0.35));

    // Sliders
    auto filterCutoffFreqSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), filterNameBounds.getBottom(), elementsBounds.getWidth() * 0.5, elementsBounds.getHeight() * 0.8);
    filterCutoffFreqSlider.setBounds(filterCutoffFreqSliderBounds);

    auto filterResonanceSliderBounds = juce::Rectangle<int>(filterCutoffFreqSliderBounds.getRight(), filterNameBounds.getBottom(), elementsBounds.getWidth() * 0.5, elementsBounds.getHeight() * 0.8);
    filterResonanceSlider.setBounds(filterResonanceSliderBounds);
}

void FilterComponent::setupFilterModeSelector(bool bypassed)
{
    if (bypassed)
    {
        filterModeSelector.setColour(juce::ComboBox::ColourIds::backgroundColourId, ColorPalette::transparentwhite);
        filterModeSelector.setColour(juce::ComboBox::ColourIds::outlineColourId, ColorPalette::bypassgrey);
        filterModeSelector.setColour(juce::ComboBox::ColourIds::textColourId, ColorPalette::bypassgrey);
        filterModeSelector.setColour(juce::ComboBox::ColourIds::arrowColourId, ColorPalette::bypassgrey);
    }
    else 
    {
        filterModeSelector.setColour(juce::ComboBox::ColourIds::backgroundColourId, ColorPalette::transparentwhite);
        filterModeSelector.setColour(juce::ComboBox::ColourIds::outlineColourId, ColorPalette::monwhite);
        filterModeSelector.setColour(juce::ComboBox::ColourIds::textColourId, ColorPalette::monwhite);
        filterModeSelector.setColour(juce::ComboBox::ColourIds::arrowColourId, ColorPalette::monwhite);
    }
}
