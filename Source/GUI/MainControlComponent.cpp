/*
  ==============================================================================

    MainControlComponent.cpp
    Metodos de MainControlComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainControlComponent.h"

//==============================================================================
MainControlComponent::MainControlComponent(juce::AudioProcessorValueTreeState& apvts, juce::String mainGainId, juce::String portamentoId)
{
    mainGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(mainGainSlider);

    addAndMakeVisible(portamentoButton);

    mainGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, mainGainId, mainGainSlider);
    portamentoButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, portamentoId, portamentoButton);
}

MainControlComponent::~MainControlComponent()
{
}

void MainControlComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void MainControlComponent::resized()
{
    mainGainSlider.setBounds(0, 0, 250, 30);
    portamentoButton.setBounds(270, 0, 30, 30);
}
