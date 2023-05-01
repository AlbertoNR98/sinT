/*
  ==============================================================================

    PresetManagerData.h
    Clase PresetManagerData -> Hereda de juce::ValueTree::Listener
        - Metodos relacionados con el manejo de presets
            - Creacion, lectura, modificacion y borrado

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class PresetManagerData : juce::ValueTree::Listener
{
public:
    PresetManagerData(juce::AudioProcessorValueTreeState& apvts);

    bool savePreset(const juce::String& presetName);
    bool deletePreset(const juce::String& presetName);
    void loadPreset(const juce::String& presetName);
    int loadPreviousPreset();
    int loadNextPreset();

    juce::String getCurrentPreset() const;
    juce::StringArray getAllPresets() const;

    static const juce::File defaultPresetDirectory;
    static const juce::String presetFileExtension;
    static const juce::String presetNameProperty;

private:
    void valueTreeRedirected(juce::ValueTree& valueTreeChanged) override;

    juce::AudioProcessorValueTreeState& apvts;
    juce::Value currentPreset;
};
