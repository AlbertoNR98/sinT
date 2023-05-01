/*
  ==============================================================================

    SettingsView.cpp
    Metodos de SettingsView

  ==============================================================================
*/

#include "SettingsView.h"

//==============================================================================
SettingsView::SettingsView() : 
    audioDeviceManager(juce::StandalonePluginHolder::getInstance()->deviceManager),
    audioSettings(audioDeviceManager, 0, 0, 0, 2, true, false, true, false)
{
    addAndMakeVisible(audioSettings);
}

SettingsView::~SettingsView()
{
}

void SettingsView::paint (juce::Graphics& g)
{
    g.setColour(ColorPalette::monwhite);
    g.setFont(44.0f);

    auto boundsPadding = 16;

    auto elementsBounds = getLocalBounds().reduced(boundsPadding);
    auto textBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() / 8);
    g.drawFittedText(viewTitle, textBounds, juce::Justification::centred, true);

    g.setColour(ColorPalette::miamiblue);
    elementsBounds.setPosition(juce::Point<int>(elementsBounds.getPosition().getX(), textBounds.getBottom() + boundsPadding));
    elementsBounds.setSize(elementsBounds.getWidth(), elementsBounds.getHeight() - textBounds.getHeight() - boundsPadding);
    g.drawRoundedRectangle(elementsBounds.toFloat(), 10.0f, 2.0f);
}

void SettingsView::resized()
{
    auto padding = 16;

    auto elementsBounds = getLocalBounds().reduced(padding);

    auto textBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() / 8);

    elementsBounds.setPosition(juce::Point<int>(elementsBounds.getPosition().getX(), textBounds.getBottom() + padding * 2));
    elementsBounds.setSize(elementsBounds.getWidth() * 0.9, elementsBounds.getHeight() - textBounds.getHeight() - padding);

    audioSettings.setBounds(elementsBounds);
}
