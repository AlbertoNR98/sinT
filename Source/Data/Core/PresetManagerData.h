/*
  ==============================================================================

    PresetManagerData.h

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class PresetManagerData : juce::ValueTree::Listener
{
public:
    PresetManagerData(juce::AudioProcessorValueTreeState& apvts);

    void savePreset(const juce::String& presetName);
    void deletePreset(const juce::String& presetName);
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
