/*
  ==============================================================================

    HomeView.cpp
    Created: 20 Oct 2022 5:39:57pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "HomeView.h"

//==============================================================================
HomeView::HomeView()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

HomeView::~HomeView()
{
}

void HomeView::paint (juce::Graphics& g)
{
    g.setColour(ColorPalette::monwhite);
    auto titleTextBounds = juce::Rectangle<int>(0, 0, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.6);
    g.setFont (180.0f);
    g.drawText ("sinT", titleTextBounds, juce::Justification::centredBottom, true);

    auto subtitleTextBounds = juce::Rectangle<int>(0, getLocalBounds().getHeight() * 0.6, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.4);
    g.setFont(45.0f);
    g.drawText("Digital Synthesizer", subtitleTextBounds, juce::Justification::centredTop, true);
}

void HomeView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
