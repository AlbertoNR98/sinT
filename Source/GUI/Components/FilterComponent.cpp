/*
  ==============================================================================

    FilterComponent.cpp
    Metodos de FilterComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterBypassedId, juce::String filterModeSelectorId, juce::String filterCutoffFreqId, juce::String filterResonanceId)
{
    addAndMakeVisible(filterBypassedButton);

    juce::StringArray waveOptions{ "LPF", "BPF", "HPF" };
    filterModeSelector.addItemList(waveOptions, 1);
    addAndMakeVisible(filterModeSelector);

    filterCutoffFreqSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(filterCutoffFreqSlider);

    filterResonanceSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(filterResonanceSlider);

    filterBypassedButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, filterBypassedId, filterBypassedButton);
    filterModeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filterModeSelectorId, filterModeSelector);
    filterCutoffFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, filterCutoffFreqId, filterCutoffFreqSlider);
    filterResonanceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, filterResonanceId, filterResonanceSlider);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::wheat);

    auto localBounds = getLocalBounds();
    g.drawRoundedRectangle(localBounds.toFloat().reduced(5.0f), 5.0f, 2.0f);

    auto textBounds = juce::Rectangle<int>(localBounds.getWidth(), localBounds.getHeight() / 6);
    textBounds.setPosition(localBounds.getPosition());
    g.setFont(24.f);
    g.drawFittedText("Filter", textBounds, juce::Justification::centred, true);
}

void FilterComponent::resized()
{
    filterBypassedButton.setBounds(0, 0, 50, 50);   // Provisional

    filterModeSelector.setBounds(0, 0, 150, 30);
    filterCutoffFreqSlider.setBounds(0, filterModeSelector.getBottom(), 300, 30);
    filterResonanceSlider.setBounds(0, filterCutoffFreqSlider.getBottom(), 300, 30);
}
