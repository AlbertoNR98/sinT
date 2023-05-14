/*
  ==============================================================================

    AudioBufferQueue.cpp
    Metodos de AudioBufferQueue

  ==============================================================================
*/

#include "AudioBufferQueue.h"

void AudioBufferQueue::push(const float* dataToPush, size_t numSamples)
{
    jassert(numSamples <= bufferSize);

    int start1, size1, start2, size2;
    abstractFifoQueue.prepareToWrite(1, start1, size1, start2, size2);

    jassert(size1 <= 1);
    jassert(size == 0);

    if (size1 > 0)
    {
        juce::FloatVectorOperations::copy(buffersQueued[(size_t)start1].data(), dataToPush, (int)juce::jmin(bufferSize, numSamples));
    }

    abstractFifoQueue.finishedWrite(size1);
}

void AudioBufferQueue::pop(float* outputData)
{
    int start1, size1, start2, size2;
    abstractFifoQueue.prepareToRead(1, start1, size1, start2, size2);

    jassert(size1 <= 1);
    jassert(size == 0);

    if (size1 > 0)
    {
        juce::FloatVectorOperations::copy(outputData, buffersQueued[(size_t)start1].data(), (int)bufferSize);
    }

    abstractFifoQueue.finishedRead(size1);
}
