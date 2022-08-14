/*
  ==============================================================================

    OscillatorData.h
    Clase OscillatorData -> Hereda de juce::dsp::Oscillator<SampleType>
        - Metodos relacionados con el procesamiento del oscilador

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

constexpr int SINE_WF{ 0 };
constexpr int SAW_WF{ 1 };
constexpr int SQUARE_WF{ 2 };

class OscillatorData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setWaveform(const int selectWaveform);
    void setGain(const float oscGainDecibels);
    void setPitch(const int newOscPitch);
    void setWaveFreq(const int midiNoteNumber);
    void setFm(const float fmFreq, const float fmDepth);
    void setOscParameters(const int selectWaveform, const float oscGainDecibels, const int oscPitch, const float fmFreq, const float fmDepth);
    float renderNextSample(float inputSample);

    void clearAll();

private:
    juce::dsp::Gain<float> oscGain;
    int oscPitch{ 0 };
    int lastMidiNote{ 0 };

    juce::dsp::Oscillator<float> fmOperator { [](float x) {return std::sin(x); } };
    float fmModulationValue{ 0.0f };
    float fmDepth{ 0.0f };
};
