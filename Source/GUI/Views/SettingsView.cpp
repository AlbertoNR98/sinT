/*
  ==============================================================================

    SettingsView.cpp
    Created: 13 Dec 2022 6:58:09pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SettingsView.h"

//==============================================================================
SettingsView::SettingsView() : audioSettings(audioDeviceManager, 0, 0, 0, 2, true, false, true, false)
{
    audioDeviceManager.initialise(0, 2, nullptr, true);
    addAndMakeVisible(audioSettings);
}

SettingsView::~SettingsView()
{
}

void SettingsView::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::wheat);
    g.setFont(44.0f);

    auto padding = 16;

    auto elementsBounds = getLocalBounds().reduced(padding);
    auto textBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() / 8);
    //g.drawRoundedRectangle(textBounds.toFloat(), 10.0f, 2.0f);
    //g.drawRect(textBounds, 5);
    g.drawFittedText(viewTitle, textBounds, juce::Justification::centred, true);

    //g.setColour(juce::Colours::black);
    elementsBounds.setPosition(juce::Point<int>(elementsBounds.getPosition().getX(), textBounds.getBottom() + padding));
    elementsBounds.setSize(elementsBounds.getWidth(), elementsBounds.getHeight() - textBounds.getHeight() - padding);
}

void SettingsView::resized()
{
    auto padding = 16;

    auto elementsBounds = getLocalBounds().reduced(padding);

    auto textBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() / 8);

    elementsBounds.setPosition(juce::Point<int>(elementsBounds.getPosition().getX(), textBounds.getBottom() + padding));
    elementsBounds.setSize(elementsBounds.getWidth(), elementsBounds.getHeight() - textBounds.getHeight() - padding);

    audioSettings.setBounds(elementsBounds);
}
