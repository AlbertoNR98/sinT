/*
  ==============================================================================

    OscillatorComponent.cpp
    Metodos de OscillatorComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscillatorComponent.h"

//==============================================================================
OscillatorComponent::OscillatorComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveformSelectorId)
{
    juce::StringArray waveOptions{ "Sine", "Saw", "Square" };
    osc1WaveSelector.addItemList(waveOptions, 1);
    addAndMakeVisible(osc1WaveSelector);

    osc1WaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveformSelectorId, osc1WaveSelector);
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
    osc1WaveSelector.setBounds(0, 0, 150, 30);
}
