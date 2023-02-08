/*
  ==============================================================================

    PresetManagerComponent.h

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Assets/ColorPalette.h"

#include "../../Data/Core/PresetManagerData.h"

//==============================================================================
/*
*/
class PresetManagerComponent : public juce::Component, juce::Button::Listener, juce::ComboBox::Listener
{
public:
    PresetManagerComponent(PresetManagerData& pmd);
    ~PresetManagerComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void setupButton(juce::Button& button, const String& buttonText);
    void setupComboBox(juce::ComboBox& comboBoxChanged);

    void loadPresetList();

    void buttonClicked(juce::Button* button) override;
    void comboBoxChanged(juce::ComboBox* comboBox) override;
    bool presetNameIsValid(const juce::String& presetName);

    juce::TextButton savePresetButton, deletePresetButton, previousPresetButton, nextPresetButton;
    juce::ComboBox presetListComboBox;
    std::unique_ptr<juce::AlertWindow> saveDialog, deleteDialog;
    enum BtnDialogReturn
    {
        CancelButtonReturn,
        OKButtonReturn
    };

    PresetManagerData& presetManagerData;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetManagerComponent)
};
