/*
  ==============================================================================

    SinTSound.h
    Clase SinTSound -> Hereda de juce::SynthesiserSound
        - Descripcion de los sonidos del sintetizador que seran lanzados por
          los objetos SinTVoice
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SinTSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }
};
