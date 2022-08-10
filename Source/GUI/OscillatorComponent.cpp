/*
  ==============================================================================

    OscillatorComponent.cpp
    Metodos de OscillatorComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscillatorComponent.h"

//==============================================================================
OscillatorComponent::OscillatorComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveformSelectorId, juce::String oscGainId, juce::String oscPitchId)
{
    juce::StringArray waveOptions{ "Sine", "Saw", "Square" };
    oscWaveSelector.addItemList(waveOptions, 1);
    addAndMakeVisible(oscWaveSelector);

    oscGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(oscGainSlider);

    oscPitchSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(oscPitchSlider);

    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveformSelectorId, oscWaveSelector);
    oscGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, oscGainId, oscGainSlider);
    oscPitchAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, oscPitchId, oscPitchSlider);
}

OscillatorComponent::~OscillatorComponent()
{
}

void OscillatorComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void OscillatorComponent::resized()
{
    oscWaveSelector.setBounds(0, 0, 150, 30);
    oscGainSlider.setBounds(0, oscWaveSelector.getBottom(), 300, 30);
    oscPitchSlider.setBounds(0, oscGainSlider.getBottom(), 300, 30);
}
