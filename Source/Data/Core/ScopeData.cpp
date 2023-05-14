/*
  ==============================================================================

    ScopeData.cpp
    Metodos de la clase ScopeData

  ==============================================================================
*/

#include "ScopeData.h"


ScopeData::ScopeData(AudioBufferQueue& queueToUse) : audioBufferQueue(queueToUse)
{
}


void ScopeData::process(const float* data, int numSamples)
{
    int index = 0;

    if (state == State::WaitingForTrigger)
    {
        while (index++ < numSamples)
        {
            auto currentSample = *data++;

            if (currentSample >= triggerLevel && previousSample < triggerLevel)
            {
                numSamplesCollected = 0;
                state = State::Collecting;
                break;
            }

            previousSample = currentSample;
        }
    }

    if (state == State::Collecting)
    {
        while (index++ < numSamples)
        {
            buffer[numSamplesCollected++] = *data++;

            if (numSamplesCollected == buffer.size())
            {
                audioBufferQueue.push(buffer.data(), buffer.size());
                state = State::WaitingForTrigger;
                previousSample = 100;
                break;
            }
        }
    }
}
