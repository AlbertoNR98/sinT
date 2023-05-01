/*
  ==============================================================================

    LFOComponent.cpp
    Metodos de LFOComponent

  ==============================================================================
*/

#include "LFOComponent.h"

//==============================================================================
LFOComponent::LFOComponent(juce::AudioProcessorValueTreeState& apvts, juce::Colour borderColour, juce::String lfoFreqId, juce::String lfoDepthId) :
    lfoFreqSlider("Frequency", "Hz"),
    lfoDepthSlider("Depth")
{
    lfoBorderColour = borderColour;

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
    g.setColour(lfoBorderColour);

    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    g.drawRoundedRectangle(localBounds, 5.0f, 2.0f);

    // Parte de arriba
    const auto boundsPadding = 16;
    auto elementsBounds = localBounds.reduced(boundsPadding);

    auto lfoNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() * 0.2);
    g.setColour(ColorPalette::monwhite);
    g.setFont(28.f);
    g.drawFittedText(lfoTitle, lfoNameBounds, juce::Justification::centred, true);

    lfoFreqSlider.applyBypassedColorPalette(false);
    lfoDepthSlider.applyBypassedColorPalette(false);
}

void LFOComponent::resized()
{
    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    const auto boundsPadding = 16;
    auto elementsBounds = localBounds.reduced(boundsPadding);

    auto heightPadding = 15;

    // Sliders
    auto lfoFreqSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), (elementsBounds.getHeight() * 0.2) + heightPadding, elementsBounds.getWidth() * 0.5, elementsBounds.getHeight() * 0.8);
    lfoFreqSlider.setBounds(lfoFreqSliderBounds);

    auto lfoDepthSliderBounds = juce::Rectangle<int>(lfoFreqSliderBounds.getRight(), (elementsBounds.getHeight() * 0.2) + heightPadding, elementsBounds.getWidth() * 0.5, elementsBounds.getHeight() * 0.8);
    lfoDepthSlider.setBounds(lfoDepthSliderBounds);
}
