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
    // getRmsValues contiene a la funcion referenciada (getRmsFunction la referencia en PluginEditor)
    // std::move transfiere el cuerpo de la funcion a la que referencia getRmsFunction hacia getRmsValues
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
    const auto rectHeight = 15;

    /*
    rmsMeterLeftChannel.setBounds(0, 0, bounds.getWidth(), bounds.getHeight() / 2.f);
    rmsMeterRightChannel.setBounds(0, (bounds.getHeight() / 2.f), bounds.getWidth(), bounds.getHeight() / 2.f);
    */

    rmsMeterLeftChannel.setBounds(0, (bounds.getHeight() * 0.25) - (rectHeight * 0.5), bounds.getWidth(), rectHeight);
    rmsMeterRightChannel.setBounds(0, (bounds.getHeight() * 0.75) - (rectHeight * 0.5), bounds.getWidth(), rectHeight);

    g.setColour(ColorPalette::darkgray);
    g.fillRoundedRectangle(rmsMeterLeftChannel, 10.0f);
    g.fillRoundedRectangle(rmsMeterRightChannel, 10.0f);

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
    const auto rectHeight = 15;

    /*
    rmsMeterLeftChannel.setBounds(0, 0, bounds.getWidth(), bounds.getHeight() / 2);
    rmsMeterRightChannel.setBounds(0, bounds.getHeight() / 2, bounds.getWidth(), bounds.getHeight());
    */

    rmsMeterLeftChannel.setBounds(0, (bounds.getHeight() * 0.25) - (rectHeight * 0.5), bounds.getWidth(), rectHeight);
    rmsMeterRightChannel.setBounds(0, (bounds.getHeight() * 0.75) - (rectHeight * 0.5), bounds.getWidth(), rectHeight);

    leftGradient = juce::ColourGradient{
        juce::Colours::green,
        rmsMeterLeftChannel.getBottomLeft(),
        juce::Colours::red,
        rmsMeterLeftChannel.getBottomRight(),
        false
    };

    leftGradient.addColour(0.5, juce::Colours::yellow);

    rightGradient = juce::ColourGradient{
        juce::Colours::green,
        rmsMeterRightChannel.getBottomLeft(),
        juce::Colours::red,
        rmsMeterRightChannel.getBottomRight(),
        false
    };

    rightGradient.addColour(0.5, juce::Colours::yellow);
}

void MeterComponent::timerCallback()
{
    repaint();
}
