/*
  ==============================================================================

    ScopeComponent.cpp
    Metodos de ScopeComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ScopeComponent.h"

//==============================================================================
ScopeComponent::ScopeComponent(AudioBufferQueue& queueToUse) : audioBufferQueue(queueToUse)
{
    bufferToPlot.fill(0.f);
    setFramesPerSecond(30);
}

ScopeComponent::~ScopeComponent()
{
    stopTimer();
}

void ScopeComponent::setFramesPerSecond(int framesPerSecond)
{
    jassert(framesPerSecond > 0 && framesPerSecond < 1000);
    startTimerHz(framesPerSecond);
}


void ScopeComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::white);

    auto area = getLocalBounds();
    auto h = area.getHeight();
    auto w = area.getWidth();

    auto scopeRect = juce::Rectangle<int>{ 0, 0, w, h };

    plot(bufferToPlot.data(), bufferToPlot.size(), g, scopeRect, 0.5, h / 2);
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
    bufferToPlot.fill(0.f);
    audioBufferQueue.pop(bufferToPlot.data());
    repaint();
}
