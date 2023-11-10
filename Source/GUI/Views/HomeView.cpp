/*
  ==============================================================================

    HomeView.cpp
    Metodos de HomeView

  ==============================================================================
*/

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
    drawTitle(g, ProjectInfo::projectName, titleTextBounds, juce::Justification::centredBottom, 140.f, 0.75f);

    auto subtitleTextBounds = juce::Rectangle<int>(0, getLocalBounds().getHeight() * 0.6, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.15);
    drawTitle(g, "Digital Polyphonic Synthesizer", subtitleTextBounds, juce::Justification::centredTop, 44.0f, 0.60f);

    auto repoTextBounds = juce::Rectangle<int>(0, getLocalBounds().getHeight() * 0.75, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.1);
    drawTitle(g, "github.com/AlbertoNR98/sinT", repoTextBounds, juce::Justification::centredBottom, 24.0f, 0.55f);

    auto versionTextBounds = juce::Rectangle<int>(0, getLocalBounds().getHeight() * 0.85, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.15);
    std::string versionText = "v";
    versionText += ProjectInfo::versionString;
    const char* pluginVersion = versionText.c_str();
    drawTitle(g, pluginVersion, versionTextBounds, juce::Justification::centredTop, 24.0f, 0.35f);
}

void HomeView::resized()
{
}
