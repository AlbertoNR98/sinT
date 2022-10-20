/*
  ==============================================================================

    MainComponent.cpp
    Created: 20 Oct 2022 5:51:21pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent(SinTAudioProcessor& audioProcessor) : containerComponent(audioProcessor.apvts), navbarComponent(audioProcessor, containerComponent)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(containerComponent);
    addAndMakeVisible(navbarComponent);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

}

void MainComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    navbarComponent.setBounds(0, 0, getWidth(), getHeight() / 8);
    containerComponent.setBounds(0, getHeight() / 8, getWidth(), getHeight() - (getHeight() / 8));
}
