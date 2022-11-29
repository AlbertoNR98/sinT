/*
  ==============================================================================

    LFOComponent.cpp
    Metodos de LFOComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LFOComponent.h"

//==============================================================================
LFOComponent::LFOComponent(juce::AudioProcessorValueTreeState& apvts, juce::String lfoFreqId, juce::String lfoDepthId) :
    lfoFreqSlider("Frequency", "Hz"),
    lfoDepthSlider("Depth")
{
    lfoFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, lfoFreqId, lfoFreqSlider.getSlider());
    lfoDepthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, lfoDepthId, lfoDepthSlider.getSlider());

    lfoFreqSlider.applyBypassedColorPalette(false);
    lfoDepthSlider.applyBypassedColorPalette(false);

    addAndMakeVisible(lfoFreqSlider);
    addAndMakeVisible(lfoDepthSlider);
}

LFOComponent::~LFOComponent()
{
}

void LFOComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::wheat);

    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    g.drawRoundedRectangle(localBounds, 5.0f, 2.0f);

    // Parte de arriba
    auto elementsBounds = localBounds.reduced(15);

    auto lfoNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() * 0.2);
    g.setColour(juce::Colours::wheat);
    g.setFont(28.f);
    g.drawFittedText(lfoTitle, lfoNameBounds, juce::Justification::centred, true);

    lfoFreqSlider.applyBypassedColorPalette(false);
    lfoDepthSlider.applyBypassedColorPalette(false);

    /*
    // Sliders -> Para debug
    auto lfoFreqSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), lfoNameBounds.getBottom(), elementsBounds.getWidth() * 0.5, elementsBounds.getHeight() * 0.8);
    auto lfoDepthSliderBounds = juce::Rectangle<int>(lfoFreqSliderBounds.getRight(), lfoNameBounds.getBottom(), elementsBounds.getWidth() * 0.5, elementsBounds.getHeight() * 0.8);
    */
}

void LFOComponent::resized()
{
    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    auto elementsBounds = localBounds.reduced(15);

    auto heightPadding = 15;
    // Sliders
    auto lfoFreqSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), (elementsBounds.getHeight() * 0.2) + heightPadding, elementsBounds.getWidth() * 0.5, elementsBounds.getHeight() * 0.8);
    lfoFreqSlider.setBounds(lfoFreqSliderBounds);

    auto lfoDepthSliderBounds = juce::Rectangle<int>(lfoFreqSliderBounds.getRight(), (elementsBounds.getHeight() * 0.2) + heightPadding, elementsBounds.getWidth() * 0.5, elementsBounds.getHeight() * 0.8);
    lfoDepthSlider.setBounds(lfoDepthSliderBounds);
}
