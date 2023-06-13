/*
  ==============================================================================

    MainComponent.cpp
    Metodos de MainComponent

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent(SinTAudioProcessor& audioProcessor) : containerComponent(audioProcessor), navbarComponent(audioProcessor, containerComponent)
{
    addAndMakeVisible(containerComponent);
    addAndMakeVisible(navbarComponent);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll(ColorPalette::basegray);
}

void MainComponent::resized()
{
    navbarComponent.setBounds(0, 0, getWidth(), getHeight() / 8);
    containerComponent.setBounds(0, getHeight() / 8, getWidth(), getHeight() - (getHeight() / 8));
}
