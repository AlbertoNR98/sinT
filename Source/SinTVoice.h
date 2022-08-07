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
#include "Data/ADSRDAta.h"

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

    void update(const float attack, const float decay, const float sustain, const float release);

private:
    ADSRData adsr;
    juce::dsp::Oscillator<float> osc1
    {
        [](float x)
        {
            return std::sin(x); // Sine
            // return x / juce::MathConstants<float>::pi; // Saw
            // return x < 0.0f ? -1.0f : 1.0f; // Square
        }       
    };
    juce::dsp::Gain<float> gainOsc1;
    bool isPrepared { false };  // Flag para controlar el renderizado
};
