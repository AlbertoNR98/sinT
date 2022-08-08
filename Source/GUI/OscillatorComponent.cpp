/*
  ==============================================================================

    OscillatorComponent.cpp
    Metodos de OscillatorComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscillatorComponent.h"

//==============================================================================
OscillatorComponent::OscillatorComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveformSelectorId, juce::String oscGainId)
{
    juce::StringArray waveOptions{ "Sine", "Saw", "Square" };
    oscWaveSelector.addItemList(waveOptions, 1);
    addAndMakeVisible(oscWaveSelector);

    oscGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(oscGainSlider);

    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveformSelectorId, oscWaveSelector);
    oscGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, oscGainId, oscGainSlider);
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
    oscGainSlider.setBounds(0, oscWaveSelector.getBottom() + 10, 300, 30);
}
