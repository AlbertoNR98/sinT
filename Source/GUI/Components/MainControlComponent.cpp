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
    mainGainSlider("Gain", "dB", CustomSliderWithLabel::SliderStyle::HorizontalCompact),
    portamentoButton("Portamento")
{
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
    auto localBounds = getLocalBounds();
    mainGainSlider.setBounds(0, 0, localBounds.getWidth() * 0.75, localBounds.getHeight());
    portamentoButton.setBounds(localBounds.getWidth() * 0.75, localBounds.getHeight() * 0.25, localBounds.getWidth() * 0.25, localBounds.getHeight() * 0.5);
}
    

void MainControlComponent::setupPortamentoButton()
{
    portamentoButton.setClickingTogglesState(true);

    //portamentoButton.setColour(juce::ComboBox::outlineColourId, juce::Colour(0xff470064));  
    portamentoButton.setColour(juce::ComboBox::outlineColourId, juce::Colours::white); //Nota: No existe juce::TextButton::outlineColourId, pero sirve juce::ComboBox::outlineColourId

    portamentoButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0x00000000));
    portamentoButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    //portamentoButton.setColour(juce::TextButton::textColourOffId, juce::Colour(0xff470064));

    portamentoButton.setColour(juce::TextButton::buttonOnColourId, juce::Colour(0xff08d85a));   // Verde
    portamentoButton.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
}
