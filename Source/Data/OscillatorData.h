/*
  ==============================================================================

    OscillatorData.h
    Clase OscillatorData -> Hereda de juce::dsp::Oscillator<SampleType>
        - Metodos relacionados con el procesamiento del oscilador

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

constexpr auto SINE_WF = 0;
constexpr auto SAW_WF = 1;
constexpr auto SQUARE_WF = 2;

class OscillatorData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setWaveform(const int selectWaveform);
    void setGain(const float oscGainDecibels);
    void setPitch(const int newOscPitch);
    void setWaveFreq(const int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& audioBlock);

private:
    juce::dsp::Gain<float> oscGain;
    int oscPitch{ 0 };
    int lastMidiNote{ 0 };

};
