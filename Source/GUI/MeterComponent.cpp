/*
  ==============================================================================

    MeterComponent.cpp
    Metodos de MeterComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MeterComponent.h"

//==============================================================================
MeterComponent::MeterComponent(std::function<std::pair<float, float>()>&& getRmsFunction) : getRmsValues(std::move(getRmsFunction))
{
    // getRmsValues apunta a la funcion referenciada (getRmsFunction la referencia en PluginEditor)
    startTimerHz(30);
}

MeterComponent::~MeterComponent()
{
    stopTimer();
}

void MeterComponent::paint (juce::Graphics& g)
{
    rmsLevels = getRmsValues();

    const auto bounds = getLocalBounds();

    rmsMeterLeftChannel.setBounds(0, 0, bounds.getWidth(), 50);
    rmsMeterRightChannel.setBounds(0, 100, bounds.getWidth(), 50);

    g.setColour(juce::Colours::grey);
    g.fillRoundedRectangle(rmsMeterLeftChannel, 5.0f);
    g.fillRoundedRectangle(rmsMeterRightChannel, 5.0f);

    g.setGradientFill(leftGradient);
    const auto scaledXLeft = juce::jmap(rmsLevels.first, -60.0f, 12.0f, 0.0f, static_cast<float>(rmsMeterLeftChannel.getWidth()));
    g.fillRoundedRectangle(rmsMeterLeftChannel.removeFromLeft(scaledXLeft), 5.0f);

    g.setGradientFill(rightGradient);
    const auto scaledXRight = juce::jmap(rmsLevels.second, -60.0f, 12.0f, 0.0f, static_cast<float>(rmsMeterRightChannel.getWidth()));
    g.fillRoundedRectangle(rmsMeterRightChannel.removeFromLeft(scaledXRight), 5.0f);
}

void MeterComponent::resized()
{
    const auto bounds = getLocalBounds();

    rmsMeterLeftChannel.setBounds(0, 0, bounds.getWidth(), 50);
    rmsMeterRightChannel.setBounds(0, 100, bounds.getWidth(), 50);

    leftGradient = juce::ColourGradient{
        juce::Colours::green,
        rmsMeterLeftChannel.getBottomRight(),
        juce::Colours::red,
        rmsMeterLeftChannel.getBottomLeft(),
        false
    };

    leftGradient.addColour(0.5, juce::Colours::yellow);

    rightGradient = juce::ColourGradient{
        juce::Colours::green,
        rmsMeterRightChannel.getBottomRight(),
        juce::Colours::red,
        rmsMeterRightChannel.getBottomLeft(),
        false
    };

    rightGradient.addColour(0.5, juce::Colours::yellow);
}

void MeterComponent::timerCallback()
{
    repaint();
}
