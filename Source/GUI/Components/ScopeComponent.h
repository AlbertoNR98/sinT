/*
  ==============================================================================

    ScopeComponent.h
    Clase ScopeComponent -> Hereda de juce::Component y de juce::Timer
        - Dibuja periodicamente los buffers de audio recogidos por ScopeData

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Assets/ColorPalette.h"
#include "../Assets/CustomLookAndFeel.h"
#include "../../Data/Core/ScopeData.h"

//==============================================================================
/*
*/
class ScopeComponent : public juce::Component, virtual CustomLookAndFeel, private juce::Timer
{
public:
    ScopeComponent(juce::String channelName, AudioBufferQueue& queueToUse);
    ~ScopeComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setFramesPerSecond(int framesPerSecond);

    void plot(const float* data,
        size_t numSamples,
        juce::Graphics& g,
        juce::Rectangle<int> rect,
        float scaler,
        float offset);

    void timerCallback() override;

private:
    juce::String channelName;

    AudioBufferQueue& audioBufferQueue;
    std::array<float, AudioBufferQueue::bufferSize> bufferToPlot;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScopeComponent)
};
