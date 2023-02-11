/*
  ==============================================================================

    SettingsView.h

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <juce_audio_plugin_client/Standalone/juce_StandaloneFilterWindow.h>

#include "../Assets/ColorPalette.h"


//==============================================================================
/*
*/
class SettingsView  : public juce::Component
{
public:
    SettingsView();
    ~SettingsView() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::String viewTitle = "Audio/MIDI Settings";

    AudioDeviceManager& audioDeviceManager;
    AudioDeviceSelectorComponent audioSettings;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsView)
};
