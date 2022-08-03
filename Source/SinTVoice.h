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
};
