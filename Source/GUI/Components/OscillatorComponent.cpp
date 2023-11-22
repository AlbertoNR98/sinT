/*
  ==============================================================================

    OscillatorComponent.cpp
    OscillatorComponent methods

  ==============================================================================
*/

#include "OscillatorComponent.h"

//==============================================================================
OscillatorComponent::OscillatorComponent(juce::String name, juce::Colour borderColour, juce::AudioProcessorValueTreeState& apvts, juce::String bypassedId, juce::String waveformSelectorId, juce::String oscGainId, juce::String oscPitchId, juce::String fmFreqId, juce::String fmDepthId) : 
    oscGainSlider("Gain", "dB"),
    oscPitchSlider("Pitch", "semitones", CustomSliderWithLabel::SliderStyle::Vertical, 0),
    fmFreqSlider("FM Frequency", "Hz"),
    fmDepthSlider("FM Depth")
{
    oscName = name;
    oscBorderColour = borderColour;

    addAndMakeVisible(oscBypassedButton);

    juce::StringArray waveOptions{ "Sine", "Saw", "Square", "Tri" };
    oscWaveSelector.addItemList(waveOptions, 1);
    oscWaveSelector.setJustificationType(juce::Justification::centred);

    oscBypassedButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, bypassedId, oscBypassedButton);
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveformSelectorId, oscWaveSelector);
    oscGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, oscGainId, oscGainSlider.getSlider());
    oscPitchAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, oscPitchId, oscPitchSlider.getSlider());
    fmFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, fmFreqId, fmFreqSlider.getSlider());
    fmDepthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, fmDepthId, fmDepthSlider.getSlider());

    auto compBypassed = oscBypassedButton.getToggleState();
    setupWaveformSelector(compBypassed);
    oscGainSlider.applyBypassedColorPalette(compBypassed);
    oscPitchSlider.applyBypassedColorPalette(compBypassed);
    fmFreqSlider.applyBypassedColorPalette(compBypassed);
    fmDepthSlider.applyBypassedColorPalette(compBypassed);

    addAndMakeVisible(oscWaveSelector);
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
    g.setColour(oscBorderColour);
    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    g.drawRoundedRectangle(localBounds, 6.0f, 3.5f);

    // Top section
    const auto boundsPadding = 16;
    auto elementsBounds = localBounds.reduced(boundsPadding);

    auto oscNameBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() * 0.55, elementsBounds.getHeight() * 0.2);
    g.setColour(ColorPalette::monwhite);
    drawTitle(g, oscName, oscNameBounds, juce::Justification::centred, 28.f, 0.4f);

    auto compBypassed = oscBypassedButton.getToggleState();
    setupWaveformSelector(compBypassed);
    oscGainSlider.applyBypassedColorPalette(compBypassed);
    oscPitchSlider.applyBypassedColorPalette(compBypassed);
    fmFreqSlider.applyBypassedColorPalette(compBypassed);
    fmDepthSlider.applyBypassedColorPalette(compBypassed);
}

void OscillatorComponent::resized()
{    
    auto localBounds = getLocalBounds().toFloat().reduced(5.0f);
    const auto boundsPadding = 16;
    auto elementsBounds = localBounds.reduced(boundsPadding);
    auto elementsTopBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() * 0.2);

    auto oscNameBounds = juce::Rectangle<int>(elementsTopBounds.getPosition().getX(), elementsTopBounds.getPosition().getY(), elementsTopBounds.getWidth() * 0.55, elementsTopBounds.getHeight());

    auto paddingWaveformSelector = 16;
    auto waveformSelectorBounds = juce::Rectangle<int>(oscNameBounds.getRight() + paddingWaveformSelector, elementsTopBounds.getPosition().getY() + paddingWaveformSelector, elementsTopBounds.getWidth() * 0.25, elementsTopBounds.getHeight() - (paddingWaveformSelector * 2));
    oscWaveSelector.setBounds(waveformSelectorBounds);

    auto bypassButtonBounds = juce::Rectangle<int>(waveformSelectorBounds.getRight() + paddingWaveformSelector + (boundsPadding * 0.5), elementsTopBounds.getPosition().getY(), (elementsTopBounds.getWidth() * 0.2) - (paddingWaveformSelector * 2) - (boundsPadding * 0.5), elementsTopBounds.getHeight());
    oscBypassedButton.setBounds(bypassButtonBounds.withSizeKeepingCentre(bypassButtonBounds.getWidth(), bypassButtonBounds.getHeight() * 0.35));

    // Sliders
    auto oscGainSliderBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsTopBounds.getBottom(), elementsBounds.getWidth() * 0.25, elementsBounds.getHeight() * 0.8);
    oscGainSlider.setBounds(oscGainSliderBounds);

    auto oscPitchSliderBounds = juce::Rectangle<int>(oscGainSliderBounds.getRight(), elementsTopBounds.getBottom(), elementsBounds.getWidth() * 0.25, elementsBounds.getHeight() * 0.8);
    oscPitchSlider.setBounds(oscPitchSliderBounds);

    auto fmFreqSliderBounds = juce::Rectangle<int>(oscPitchSliderBounds.getRight(), elementsTopBounds.getBottom(), elementsBounds.getWidth() * 0.25, elementsBounds.getHeight() * 0.8);
    fmFreqSlider.setBounds(fmFreqSliderBounds);

    auto fmDepthSliderBounds = juce::Rectangle<int>(fmFreqSliderBounds.getRight(), elementsTopBounds.getBottom(), elementsBounds.getWidth() * 0.25, elementsBounds.getHeight() * 0.8);
    fmDepthSlider.setBounds(fmDepthSliderBounds);
}

void OscillatorComponent::setupWaveformSelector(bool bypassed)
{
    if (bypassed)
    {
        oscWaveSelector.setColour(juce::ComboBox::ColourIds::backgroundColourId, ColorPalette::transparentwhite);
        oscWaveSelector.setColour(juce::ComboBox::ColourIds::outlineColourId, ColorPalette::bypassgrey);
        oscWaveSelector.setColour(juce::ComboBox::ColourIds::textColourId, ColorPalette::bypassgrey);
        oscWaveSelector.setColour(juce::ComboBox::ColourIds::arrowColourId, ColorPalette::bypassgrey);
    }
    else
    {
        oscWaveSelector.setColour(juce::ComboBox::ColourIds::backgroundColourId, ColorPalette::transparentwhite);
        oscWaveSelector.setColour(juce::ComboBox::ColourIds::outlineColourId, ColorPalette::monwhite);
        oscWaveSelector.setColour(juce::ComboBox::ColourIds::textColourId, ColorPalette::monwhite);
        oscWaveSelector.setColour(juce::ComboBox::ColourIds::arrowColourId, ColorPalette::monwhite);
    }
}
