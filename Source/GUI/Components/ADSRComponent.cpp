/*
  ==============================================================================

    ADSRComponent.cpp
    Metodos de ADSRComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRComponent.h"

//==============================================================================
ADSRComponent::ADSRComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId) :
    attackSlider("Attack", "s"),
    decaySlider("Decay", "s"),
    sustainSlider("Sustain", "s"),
    releaseSlider("Release", "s")
{
    adsrName = name;
    
    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, attackId, attackSlider.getSlider());
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, decayId, decaySlider.getSlider());
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, sustainId, sustainSlider.getSlider());
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, releaseId, releaseSlider.getSlider());

    attackSlider.applyBypassedColorPalette(false);
    decaySlider.applyBypassedColorPalette(false);
    sustainSlider.applyBypassedColorPalette(false);
    releaseSlider.applyBypassedColorPalette(false);

    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySlider);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);
}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::wheat);

    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    g.drawRoundedRectangle(localBounds, 5.0f, 2.0f);

    // Parte de arriba
    auto elementsBounds = localBounds.reduced(15);

    auto adsrNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() * 0.2);
    g.setColour(juce::Colours::wheat);
    g.setFont(28.f);
    g.drawFittedText(adsrName, adsrNameBounds, juce::Justification::centred, true);

    attackSlider.applyBypassedColorPalette(false);
    decaySlider.applyBypassedColorPalette(false);
    sustainSlider.applyBypassedColorPalette(false);
    releaseSlider.applyBypassedColorPalette(false);
}

void ADSRComponent::resized()
{
    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    auto elementsBounds = localBounds.reduced(15);

    auto adsrNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.55, elementsBounds.getHeight() * 0.2);
    auto heightPadding = 15;

    // Sliders
    auto attackSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), adsrNameBounds.getBottom() + heightPadding, elementsBounds.getWidth() * 0.25, (elementsBounds.getHeight() * 0.8) - heightPadding);
    attackSlider.setBounds(attackSliderBounds);

    auto decaySliderBounds = juce::Rectangle<int>(attackSliderBounds.getRight(), adsrNameBounds.getBottom() + heightPadding, elementsBounds.getWidth() * 0.25, (elementsBounds.getHeight() * 0.8) - heightPadding);
    decaySlider.setBounds(decaySliderBounds);

    auto sustainSliderBounds = juce::Rectangle<int>(decaySliderBounds.getRight(), adsrNameBounds.getBottom() + heightPadding, elementsBounds.getWidth() * 0.25, (elementsBounds.getHeight() * 0.8) - heightPadding);
    sustainSlider.setBounds(sustainSliderBounds);

    auto releaseSliderBounds = juce::Rectangle<int>(sustainSliderBounds.getRight(), adsrNameBounds.getBottom() + heightPadding, elementsBounds.getWidth() * 0.25, (elementsBounds.getHeight() * 0.8) - heightPadding);
    releaseSlider.setBounds(releaseSliderBounds);
}
