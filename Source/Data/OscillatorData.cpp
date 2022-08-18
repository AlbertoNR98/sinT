/*
  ==============================================================================

    OscillatorData.cpp
    Metodos de OscillatorData

  ==============================================================================
*/

#include "OscillatorData.h"

void OscillatorData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    resetAll();

    prepare(spec);
    fmOperator.prepare(spec);
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

void OscillatorData::setPitch(const int newOscPitch)
{
    oscPitch = newOscPitch;
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(lastMidiNote + oscPitch) + fmModulationValue);
}

void OscillatorData::setWaveFreq(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber + oscPitch) + fmModulationValue);
    lastMidiNote = midiNoteNumber;
}

void OscillatorData::setFm(const float fmFreq, const float fmDepth)
{
    fmOperator.setFrequency(fmFreq);
    this->fmDepth = fmDepth;
    auto currentOscFreq = juce::MidiMessage::getMidiNoteInHertz(lastMidiNote + oscPitch) + fmModulationValue;
    if (currentOscFreq >= 0)
    {
        setFrequency(currentOscFreq);
    }
    else 
    {
        setFrequency(currentOscFreq * -1.0f);
    }
}

void OscillatorData::setParameters(const int selectWaveform, const float oscGainDecibels, const int oscPitch, const float fmFreq, const float fmDepth)
{
    setWaveform(selectWaveform);
    setGain(oscGainDecibels);
    setPitch(oscPitch);
    setFm(fmFreq, fmDepth);
}

float OscillatorData::renderNextSample(float inputSample)
{
    fmModulationValue = fmOperator.processSample(inputSample) * fmDepth;
    return oscGain.processSample(processSample(inputSample));
}

void OscillatorData::resetAll()
{
    reset();
    fmOperator.reset();
    oscGain.reset();
}
