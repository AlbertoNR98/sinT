/*
  ==============================================================================

    SettingsView.h
    Clase SettingsView -> Hereda de juce::Component
        - Vista de settings -> Disponible en Kiosk Mode

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <juce_audio_plugin_client/Standalone/juce_StandaloneFilterWindow.h>
#include "../Assets/ColorPalette.h"
#include "../Assets/CustomLookAndFeel.h"


//==============================================================================
/*
*/
class SettingsView : public juce::Component, virtual CustomLookAndFeel
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

    class AudioSettingsLookAndFeel : public LookAndFeel_V4
    {
    public:
        AudioSettingsLookAndFeel();
        ~AudioSettingsLookAndFeel() override;

        virtual void drawButtonText(Graphics& g, TextButton& button,
            [[maybe_unused]] bool shouldDrawButtonAsHighlighted, [[maybe_unused]] bool shouldDrawButtonAsDown) override;

        virtual void drawPopupMenuBackground(Graphics& g, int width, int height) override;

        virtual void drawPopupMenuItem(Graphics& g, const Rectangle<int>& area,
            const bool isSeparator, const bool isActive,
            const bool isHighlighted, const bool isTicked,
            const bool hasSubMenu, const String& text,
            const String& shortcutKeyText,
            [[maybe_unused]] const Drawable* icon, const Colour* const textColourToUse) override;
        
        virtual void drawLabel(Graphics& g, Label& label) override;

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioSettingsLookAndFeel)
    }audioSettingsLnF;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsView)
};
