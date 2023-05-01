/*
  ==============================================================================

    MainControlComponent.cpp
    Metodos de MainControlComponent

  ==============================================================================
*/

#include "MainControlComponent.h"

//==============================================================================
MainControlComponent::MainControlComponent(juce::AudioProcessorValueTreeState& apvts, juce::String mainGainId, juce::String portamentoId) :
    mainGainSlider("Gain", "dB", CustomSliderWithLabel::SliderStyle::HorizontalCompact),
    portamentoButton("Portamento")
{
    setupGainSlider();
    addAndMakeVisible(mainGainSlider);

    setupPortamentoButton();
    addAndMakeVisible(portamentoButton);

    mainGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, mainGainId, mainGainSlider.getSlider());
    portamentoButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(apvts, portamentoId, portamentoButton);
}

MainControlComponent::~MainControlComponent()
{
}

void MainControlComponent::paint (juce::Graphics& g)
{
}

void MainControlComponent::resized()
{
    const auto localBounds = getLocalBounds();
    mainGainSlider.setBounds(0, 0, localBounds.getWidth() * 0.70, localBounds.getHeight());
    portamentoButton.setBounds(localBounds.getWidth() * 0.70, localBounds.getHeight() * 0.30, localBounds.getWidth() * 0.30, localBounds.getHeight() * 0.5);
}
    
void MainControlComponent::setupGainSlider()
{
    mainGainSlider.getSlider().setColour(juce::Slider::ColourIds::backgroundColourId, ColorPalette::darkgray);
    mainGainSlider.getSlider().setColour(juce::Slider::ColourIds::trackColourId, ColorPalette::miamipink);
    mainGainSlider.getSlider().setColour(juce::Slider::ColourIds::thumbColourId, ColorPalette::miamiblue);
}

void MainControlComponent::setupPortamentoButton()
{
    portamentoButton.setClickingTogglesState(true);

    portamentoButton.setColour(juce::ComboBox::outlineColourId, ColorPalette::monwhite); //Nota: No existe juce::TextButton::outlineColourId, pero sirve juce::ComboBox::outlineColourId

    portamentoButton.setColour(juce::TextButton::buttonColourId, ColorPalette::transparentblack);
    portamentoButton.setColour(juce::TextButton::textColourOffId, ColorPalette::monwhite);

    portamentoButton.setColour(juce::TextButton::buttonOnColourId, ColorPalette::betis);   // Verde
    portamentoButton.setColour(juce::TextButton::textColourOnId, ColorPalette::monwhite);
}
