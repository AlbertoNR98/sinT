/*
  ==============================================================================

    OscillatorComponent.cpp
    Metodos de OscillatorComponent

  ==============================================================================
*/

#include "OscillatorComponent.h"

//==============================================================================
OscillatorComponent::OscillatorComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String bypassedId, juce::String waveformSelectorId, juce::String oscGainId, juce::String oscPitchId, juce::String fmFreqId, juce::String fmDepthId) : 
    oscGainSlider("Gain", "dB"),
    oscPitchSlider("Pitch", "semitones", true, 0),
    fmFreqSlider("FM Frequency", "Hz"),
    fmDepthSlider("FM Depth", "")
{
    oscName = name;

    addAndMakeVisible(oscBypassedButton);

    juce::StringArray waveOptions{ "Sine", "Saw", "Square" };
    oscWaveSelector.addItemList(waveOptions, 1);

    oscWaveSelector.setColour(juce::ComboBox::ColourIds::backgroundColourId, ColorPalette::darkgray);
    addAndMakeVisible(oscWaveSelector);

    oscBypassedButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, bypassedId, oscBypassedButton);
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveformSelectorId, oscWaveSelector);
    oscGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, oscGainId, oscGainSlider.getSlider());
    oscPitchAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, oscPitchId, oscPitchSlider.getSlider());
    fmFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, fmFreqId, fmFreqSlider.getSlider());
    fmDepthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, fmDepthId, fmDepthSlider.getSlider());

    auto compBypassed = oscBypassedButton.getToggleState();
    oscGainSlider.applyColorPalette(compBypassed);
    oscPitchSlider.applyColorPalette(compBypassed);
    fmFreqSlider.applyColorPalette(compBypassed);
    fmDepthSlider.applyColorPalette(compBypassed);

    addAndMakeVisible(oscGainSlider);
    addAndMakeVisible(oscPitchSlider);
    addAndMakeVisible(fmFreqSlider);
    addAndMakeVisible(fmDepthSlider);
}

OscillatorComponent::~OscillatorComponent()
{
}

void OscillatorComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::wheat);

    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    g.drawRoundedRectangle(localBounds, 5.0f, 2.0f);

    // Parte de arriba
    auto elementsBounds = localBounds.reduced(15);

    auto oscNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.55, elementsBounds.getHeight() * 0.2);
    g.setColour(juce::Colours::wheat);
    g.setFont(28.f);
    g.drawFittedText(oscName, oscNameBounds, juce::Justification::centredLeft, true);

    auto waveformSelectorBoundsWithoutPadding = juce::Rectangle<int>(oscNameBounds.getRight(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.3, elementsBounds.getHeight() * 0.2);
    
    auto paddingWaveformSelector = 15;
    auto waveformSelectorBounds = juce::Rectangle<int>(oscNameBounds.getRight(), elementsBounds.getPosition().getY() + paddingWaveformSelector, elementsBounds.getWidth() * 0.3, (elementsBounds.getHeight() * 0.2) - (2 * paddingWaveformSelector));

    auto bypassButtonBounds = juce::Rectangle<int>(waveformSelectorBounds.getRight(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.15, elementsBounds.getHeight() * 0.2);

    // Sliders
    auto oscGainSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), bypassButtonBounds.getBottom(), elementsBounds.getWidth() * 0.25, elementsBounds.getHeight() * 0.8);
    auto oscPitchSliderBounds = juce::Rectangle<int>(oscGainSliderBounds.getRight(), bypassButtonBounds.getBottom(), elementsBounds.getWidth() * 0.25, elementsBounds.getHeight() * 0.8);
    auto fmFreqSliderBounds = juce::Rectangle<int>(oscPitchSliderBounds.getRight(), bypassButtonBounds.getBottom(), elementsBounds.getWidth() * 0.25, elementsBounds.getHeight() * 0.8);
    auto fmDepthSliderBounds = juce::Rectangle<int>(fmFreqSliderBounds.getRight(), bypassButtonBounds.getBottom(), elementsBounds.getWidth() * 0.25, elementsBounds.getHeight() * 0.8);

    auto compBypassed = oscBypassedButton.getToggleState();
    oscGainSlider.applyColorPalette(compBypassed);
    oscPitchSlider.applyColorPalette(compBypassed);
    fmFreqSlider.applyColorPalette(compBypassed);
    fmDepthSlider.applyColorPalette(compBypassed);
}

void OscillatorComponent::resized()
{    
    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    auto elementsBounds = localBounds.reduced(15);

    auto oscNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.55, elementsBounds.getHeight() * 0.2);

    auto paddingWaveformSelector = 15;
    auto waveformSelectorBounds = juce::Rectangle<int>(oscNameBounds.getRight(), elementsBounds.getPosition().getY() + paddingWaveformSelector, elementsBounds.getWidth() * 0.3, (elementsBounds.getHeight() * 0.2) - (2 * paddingWaveformSelector));
    oscWaveSelector.setBounds(waveformSelectorBounds);

    auto bypassButtonBounds = juce::Rectangle<int>(waveformSelectorBounds.getRight(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.15, elementsBounds.getHeight() * 0.2);
    oscBypassedButton.setBounds(bypassButtonBounds);
    oscBypassedButton.setTopLeftPosition(juce::Point<int>(bypassButtonBounds.getCentre().getX(), bypassButtonBounds.getTopLeft().getY()));

    // Sliders
    auto oscGainSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), bypassButtonBounds.getBottom(), elementsBounds.getWidth() * 0.25, elementsBounds.getHeight() * 0.8);
    oscGainSlider.setBounds(oscGainSliderBounds);

    auto oscPitchSliderBounds = juce::Rectangle<int>(oscGainSliderBounds.getRight(), bypassButtonBounds.getBottom(), elementsBounds.getWidth() * 0.25, elementsBounds.getHeight() * 0.8);
    oscPitchSlider.setBounds(oscPitchSliderBounds);

    auto fmFreqSliderBounds = juce::Rectangle<int>(oscPitchSliderBounds.getRight(), bypassButtonBounds.getBottom(), elementsBounds.getWidth() * 0.25, elementsBounds.getHeight() * 0.8);
    fmFreqSlider.setBounds(fmFreqSliderBounds);

    auto fmDepthSliderBounds = juce::Rectangle<int>(fmFreqSliderBounds.getRight(), bypassButtonBounds.getBottom(), elementsBounds.getWidth() * 0.25, elementsBounds.getHeight() * 0.8);
    fmDepthSlider.setBounds(fmDepthSliderBounds);
}
