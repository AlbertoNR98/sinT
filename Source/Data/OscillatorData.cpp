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
    auto pitchWheelRatio = juce::jmap(static_cast<float>(lastPitchWheel), 0.0f, 16383.0f, FREQ_LRATIO, FREQ_HRATIO);
    setFrequency(pitchWheelRatio * (juce::MidiMessage::getMidiNoteInHertz(lastMidiNote + oscPitch) + fmModulationValue), true);   // Sin portamento
    //setFrequency(pitchWheelRatio * (juce::MidiMessage::getMidiNoteInHertz(lastMidiNote + oscPitch) + fmModulationValue));   // Con portamento
}

void OscillatorData::setPitchWheel(const int newPitchWheel)
{
    // Map entre los valores que devuelve la rueda y el factor de relacion entre frecuencia e intervalo.
    // La rueda sube/baja un tono. Con una frecuencia f, la nueva frecuencia ira de 1/2(2^12) * f a 2(2^12) * f
    lastPitchWheel = newPitchWheel;
}


void OscillatorData::setWaveFreq(const int midiNoteNumber, const int currentPitchWheelPosition)
{
    lastPitchWheel = currentPitchWheelPosition;

    auto pitchWheelRatio = juce::jmap(static_cast<float>(lastPitchWheel), 0.0f, 16383.0f, FREQ_LRATIO, FREQ_HRATIO);
    setFrequency(pitchWheelRatio * (juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber + oscPitch) + fmModulationValue), true); // Sin portamento
    //setFrequency(pitchWheelRatio * (juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber + oscPitch) + fmModulationValue)); // Con portamento

    lastMidiNote = midiNoteNumber;

    //DBG(lastPitchWheel);
}

void OscillatorData::setFmSynthesis(const float fmFreq, const float fmDepth)
{
    fmOperator.setFrequency(fmFreq);
    this->fmDepth = fmDepth;
    if (fmFreq == 0.0f) fmModulationValue = 0.0f;
    
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
    setFmSynthesis(fmFreq, fmDepth);
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
