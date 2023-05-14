/*
  ==============================================================================

    AudioBufferQueue.h
    Clase AudioBufferQueue
        - Cola de buffers de audio -> samples de tipo float
        - Implementa logica de juce::AbstractFifo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AudioBufferQueue
{
public:
    static constexpr size_t order = 10;
    static constexpr size_t bufferSize = 1U << order;  //1U << order = 2^order
    static constexpr size_t numBuffers = 5;

    void push(const float* dataToPush, size_t numSamples);
    void pop(float* outputData);

private:
    juce::AbstractFifo abstractFifoQueue{ numBuffers };
    std::array<std::array<float, bufferSize>, numBuffers> buffersQueued;
};