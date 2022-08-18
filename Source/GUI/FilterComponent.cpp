/*
  ==============================================================================

    FilterComponent.cpp
    Metodos de FilterComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterModeSelectorId, juce::String filterCutoffFreqId, juce::String filterResonanceId)
{
    juce::StringArray waveOptions{ "LPF", "BPF", "HPF" };
    filterModeSelector.addItemList(waveOptions, 1);
    addAndMakeVisible(filterModeSelector);

    filterCutoffFreqSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(filterCutoffFreqSlider);

    filterResonanceSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(filterResonanceSlider);

    filterModeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filterModeSelectorId, filterModeSelector);
    filterCutoffFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, filterCutoffFreqId, filterCutoffFreqSlider);
    filterResonanceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, filterResonanceId, filterResonanceSlider);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void FilterComponent::resized()
{
    filterModeSelector.setBounds(0, 0, 150, 30);
    filterCutoffFreqSlider.setBounds(0, filterModeSelector.getBottom(), 300, 30);
    filterResonanceSlider.setBounds(0, filterCutoffFreqSlider.getBottom(), 300, 30);
}
