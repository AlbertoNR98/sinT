/*
  ==============================================================================

    ScopeComponent.cpp
    Metodos de ScopeComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ScopeComponent.h"

//==============================================================================
ScopeComponent::ScopeComponent(juce::String channelName, AudioBufferQueue& queueToUse) : audioBufferQueue(queueToUse)
{
    this->channelName = channelName;
    bufferToPlot.fill(0.f);
    setFramesPerSecond(30);
}

ScopeComponent::~ScopeComponent()
{
    stopTimer();
}

void ScopeComponent::setFramesPerSecond(int framesPerSecond)
{
    startTimerHz(framesPerSecond);
}


void ScopeComponent::paint (juce::Graphics& g)
{
    auto area = getLocalBounds();
    auto h = area.getHeight();
    auto w = area.getWidth();

    auto scopeArea = juce::Rectangle<int>{ 0, 0, w, h };

    auto channelNameArea = scopeArea;
    channelNameArea.setSize(scopeArea.getWidth() * 0.1f, scopeArea.getHeight() * 0.15f);

    g.setColour(ColorPalette::monwhite.withAlpha(0.4f));
    drawTitle(g, channelName, channelNameArea, juce::Justification::centredBottom, 16.0f, 0.75f);

    plot(bufferToPlot.data(), bufferToPlot.size(), g, scopeArea, 0.5, h / 2);
}


void ScopeComponent::plot(const float* data,
    size_t numSamples,
    juce::Graphics& g,
    juce::Rectangle<int> rect,
    float scaler = 1.f,
    float offset = 0.f)
{
    auto w = rect.getWidth();
    auto h = rect.getHeight();
    auto right = rect.getRight();

    auto center = rect.getBottom() - offset;
    auto gain = h * scaler;

    g.setColour(ColorPalette::monwhite);

    for (size_t i = 1; i < numSamples; ++i)
    {
        g.drawLine({ juce::jmap(float(i - 1), float(0), float(numSamples - 1), float(right - w), float(right)),
              center - gain * data[i - 1],
              juce::jmap(float(i), float(0), float(numSamples - 1), float(right - w), float(right)),
              center - gain * data[i] }, 3.f);
    }
}

void ScopeComponent::resized()
{
}

void ScopeComponent::timerCallback()
{
    audioBufferQueue.pop(bufferToPlot.data());
    repaint();
}
