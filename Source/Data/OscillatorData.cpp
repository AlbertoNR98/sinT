/*
  ==============================================================================

    OscillatorData.cpp
    Metodos de OscillatorData

  ==============================================================================
*/

#include "OscillatorData.h"

void OscillatorData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    prepare(spec);
    oscGain.prepare(spec);
}

void OscillatorData::setWaveform(const int selectWaveform)
{
    switch (selectWaveform)
    {
    case SINE_WF:
        initialise([](float x) { return std::sin(x); });
        break;
    case SAW_WF:
        initialise([](float x) { return x / juce::MathConstants<float>::pi; });
        break;
    case SQUARE_WF:
        initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; });
        break;
    default:
        jassertfalse;
        break;
    }
}

void OscillatorData::setGain(const float oscGainDecibels)
{
    oscGain.setGainDecibels(oscGainDecibels);
}

void OscillatorData::setWaveFreq(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
}

void OscillatorData::getNextAudioBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    oscGain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}
