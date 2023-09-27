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
    g.setFont(180.0f);
    g.drawText(ProjectInfo::projectName, titleTextBounds, juce::Justification::centredBottom, true);

    auto subtitleTextBounds = juce::Rectangle<int>(0, getLocalBounds().getHeight() * 0.6, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.15);
    g.setFont(45.0f);
    g.drawText("Digital Polyphonic Synthesizer", subtitleTextBounds, juce::Justification::centredTop, true);

    auto repoTextBounds = juce::Rectangle<int>(0, getLocalBounds().getHeight() * 0.75, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.1);
    g.setFont(24.0f);
    g.drawText("github.com/AlbertoNR98/sinT", repoTextBounds, juce::Justification::centredBottom, true);

    auto versionTextBounds = juce::Rectangle<int>(0, getLocalBounds().getHeight() * 0.85, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.15);
    g.setFont(24.0f);
    std::string versionText = "v";
    versionText += ProjectInfo::versionString;
    const char* pluginVersion = versionText.c_str();
    g.drawText(pluginVersion, versionTextBounds, juce::Justification::centredTop, true);
}

void HomeView::resized()
{
}
