/*
  ==============================================================================

    HomeView.cpp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "HomeView.h"

//==============================================================================
HomeView::HomeView()
{
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

    auto subtitleTextBounds = juce::Rectangle<int>(0, getLocalBounds().getHeight() * 0.6, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.15);
    g.setFont(45.0f);
    g.drawText("Digital Polyphonic Synthesizer", subtitleTextBounds, juce::Justification::centredTop, true);

    auto nameTextBounds = juce::Rectangle<int>(0, getLocalBounds().getHeight() * 0.75, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.1);
    g.setFont(24.0f);
    g.drawText("Alberto Naranjo Rodriguez", nameTextBounds, juce::Justification::centredBottom, true);

    auto repoTextBounds = juce::Rectangle<int>(0, getLocalBounds().getHeight() * 0.85, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.15);
    g.setFont(24.0f);
    g.drawText("github.com/AlbertoNR98/sinT", repoTextBounds, juce::Justification::centredTop, true);
}

void HomeView::resized()
{
}
