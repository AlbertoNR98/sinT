/*
  ==============================================================================

    SinTVoice.h
    Clase SinTVoice -> Hereda de juce::SynthesiserVoice
        - Lanzan los sonidos descritos en SinTSound

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SinTSound.h"
#include "Data/ADSRData.h"
#include "Data/OscillatorData.h"
#include "Data/FilterData.h"

constexpr int numVoiceChannels{ 2 };

class SinTVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    void setModParameters(const int filterMode, const float filterCutoffFreq, const float filterResonance);

    void resetAll();

    std::array<OscillatorData, numVoiceChannels>& getOscillator1() { return osc1; };
    std::array<OscillatorData, numVoiceChannels>& getOscillator2() { return osc2; };
    ADSRData& getADSR() { return adsr; };

private:
    std::array<OscillatorData, numVoiceChannels> osc1;
    std::array<OscillatorData, numVoiceChannels> osc2;
    ADSRData adsr;
    std::array<FilterData, numVoiceChannels> filter;

    juce::AudioBuffer<float> voiceBuffer; // Buffer auxiliar que contiene las muestras asociadas a la voz actual
    juce::dsp::Gain<float> voiceGain;
};
