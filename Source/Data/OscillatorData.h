/*
  ==============================================================================

    OscillatorData.h
    Clase OscillatorData -> Hereda de juce::dsp::Oscillator<SampleType>
        - Metodos relacionados con el procesamiento del oscilador

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

static constexpr int SINE_WF{ 0 };
static constexpr int SAW_WF{ 1 };
static constexpr int SQUARE_WF{ 2 };

static constexpr float FREQ_LRATIO{ 0.890898718 };  // 1/2^(2/12)
static constexpr float FREQ_HRATIO{ 1.122462048 };  // 2^(2/12)

class OscillatorData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setWaveform(const int selectWaveform);
    void setGain(const float oscGainDecibels);
    void setPitch(const int newOscPitch);
    void setPitchWheel(const int newPitchWheel);
    void setWaveFreq(const int midiNoteNumber, const int currentPitchWheelPosition);
    void setFmSynthesis(const float fmFreq, const float fmDepth);
    void setParameters(const int selectWaveform, const float oscGainDecibels, const int oscPitch, const float fmFreq, const float fmDepth);
    float renderNextSample(float inputSample);

    void resetAll();

private:
    juce::dsp::Gain<float> oscGain;
    int oscPitch{ 0 };
    int lastPitchWheel{ 8192 };
    int lastMidiNote{ 0 };

    juce::dsp::Oscillator<float> fmOperator { [](float x) {return std::sin(x); } };
    float fmModulationValue{ 0.0f };
    float fmDepth{ 0.0f };
};
