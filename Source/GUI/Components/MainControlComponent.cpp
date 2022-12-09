/*
  ==============================================================================

    MainControlComponent.cpp
    Metodos de MainControlComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainControlComponent.h"

//==============================================================================
MainControlComponent::MainControlComponent(juce::AudioProcessorValueTreeState& apvts, juce::String mainGainId, juce::String portamentoId) :
    mainGainSlider("Gain", "dB", CustomSliderWithLabel::SliderStyle::HorizontalCompact)
{
    //mainGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(mainGainSlider);

    addAndMakeVisible(portamentoButton);

    //mainGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, mainGainId, mainGainSlider);
    mainGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, mainGainId, mainGainSlider.getSlider());
    portamentoButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, portamentoId, portamentoButton);
}

MainControlComponent::~MainControlComponent()
{
}

void MainControlComponent::paint (juce::Graphics& g)
{
    //g.fillAll (juce::Colours::black);
    //g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.drawRect(getLocalBounds());
}

void MainControlComponent::resized()
{
    auto localBounds = getLocalBounds();
    mainGainSlider.setBounds(0, 0, localBounds.getWidth() * 0.85, localBounds.getHeight());
    portamentoButton.setBounds(localBounds.getWidth() * 0.85, 0, localBounds.getWidth() * 0.15, localBounds.getHeight());
}
