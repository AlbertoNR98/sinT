/*
  ==============================================================================

    ScopeData.h
    Clase ScopeData
        - Se encarga de encolar los buffers de audio una vez se supere el umbral de trigger

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Assets/AudioBufferQueue.h"

class ScopeData
{
public:
    ScopeData(AudioBufferQueue& queueToUse);
    ~ScopeData() {};

    void process(const float* data, int numSamples);
    
private:
    AudioBufferQueue& audioBufferQueue;
    std::array<float, AudioBufferQueue::bufferSize> buffer {};
    size_t numSamplesCollected = 0;

    float previousSample = 100;

    static constexpr auto triggerLevel = 0.005f;

    enum class State { WaitingForTrigger, Collecting } state { State::WaitingForTrigger };

};
