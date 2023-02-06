/*
  ==============================================================================

    PresetManagerComponent.cpp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PresetManagerComponent.h"

//==============================================================================
PresetManagerComponent::PresetManagerComponent(PresetManagerData& pmd) : presetManagerData(pmd)
{
    setupButton(savePresetButton, "Save");
    setupButton(deletePresetButton, "Delete");
    setupButton(previousPresetButton, "<");
    setupButton(nextPresetButton, ">");

    setupComboBox(presetListComboBox);

    loadPresetList();
}

PresetManagerComponent::~PresetManagerComponent()
{
    savePresetButton.removeListener(this);
    deletePresetButton.removeListener(this);
    previousPresetButton.removeListener(this);
    nextPresetButton.removeListener(this);
    presetListComboBox.removeListener(this);
}

void PresetManagerComponent::paint (juce::Graphics& g)
{

}

void PresetManagerComponent::resized()
{
    //const auto container = getLocalBounds().reduced(4);
    const auto container = getLocalBounds();
    auto bounds = container;

    savePresetButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.15f)).reduced(4));
    previousPresetButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.1f)).reduced(8));
    presetListComboBox.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.5f)).reduced(4));
    nextPresetButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.1f)).reduced(8));
    deletePresetButton.setBounds(bounds.reduced(4));
}

void PresetManagerComponent::setupButton(juce::Button& button, const String& buttonText)
{
    button.setButtonText(buttonText);

    button.setColour(juce::ComboBox::outlineColourId, juce::Colours::white);
    button.setColour(juce::TextButton::buttonColourId, juce::Colour(0x00000000));   // Transparent black

    addAndMakeVisible(button);
    button.addListener(this);
}

void PresetManagerComponent::setupComboBox(juce::ComboBox& comboBox)
{
    comboBox.setJustificationType(juce::Justification::centred);
    comboBox.setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colour(0x00000000));
    comboBox.setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::white);

    comboBox.setTextWhenNoChoicesAvailable("No Preset Selected");
    comboBox.setTextWhenNothingSelected("No Preset Selected");
    addAndMakeVisible(comboBox);
    comboBox.addListener(this);
}

void PresetManagerComponent::loadPresetList()
{
    presetListComboBox.clear(dontSendNotification);

    const auto allPresets = presetManagerData.getAllPresets();
    const auto currentPreset = presetManagerData.getCurrentPreset();
    presetListComboBox.addItemList(allPresets, 1);
    presetListComboBox.setSelectedItemIndex(allPresets.indexOf(currentPreset), dontSendNotification);
}

void PresetManagerComponent::buttonClicked(juce::Button* button)
{
    if (button == &savePresetButton)
    {
        saveDialog = std::make_unique<juce::AlertWindow>("Save a Preset",
            "Name the Preset",
            juce::AlertWindow::NoIcon,
            nullptr
        );
        saveDialog->addTextEditor("presetNameEditor", "");
        saveDialog->addButton("Save", BtnDialogReturn::SaveButtonReturn, KeyPress(KeyPress::returnKey));
        saveDialog->addButton("Cancel", BtnDialogReturn::CancelButtonReturn, KeyPress(KeyPress::escapeKey));

        saveDialog->enterModalState(true, ModalCallbackFunction::create([this](int btnClicked)
            {
                switch (btnClicked)
                {
                case BtnDialogReturn::SaveButtonReturn:
                    if (presetNameIsValid(saveDialog->getTextEditorContents("presetNameEditor")))
                    {
                        presetManagerData.savePreset(saveDialog->getTextEditorContents("presetNameEditor"));
                        AlertWindow::showMessageBoxAsync(AlertWindow::NoIcon, saveDialog->getTextEditorContents("presetNameEditor") + " saved as a preset.", "");
                        loadPresetList();
                    }
                    else {
                        AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "Name is not valid. Can't save the preset.", "");
                    }
                    break;
                case BtnDialogReturn::CancelButtonReturn:
                default:
                    break;
                }
                saveDialog->exitModalState(btnClicked);
                saveDialog->setVisible(false);
            }));
    }

    if (button == &previousPresetButton)
    {
        const auto index = presetManagerData.loadPreviousPreset();
        presetListComboBox.setSelectedItemIndex(index, dontSendNotification);
    }

    if (button == &nextPresetButton)
    {
        const auto index = presetManagerData.loadNextPreset();
        presetListComboBox.setSelectedItemIndex(index, dontSendNotification);
    }

    if (button == &deletePresetButton)
    {
        presetManagerData.deletePreset(presetManagerData.getCurrentPreset());
        loadPresetList();
    }
}

void PresetManagerComponent::comboBoxChanged(juce::ComboBox* comboBoxChanged)
{
    if (comboBoxChanged == &presetListComboBox)
    {
        presetManagerData.loadPreset(presetListComboBox.getItemText(presetListComboBox.getSelectedItemIndex()));
    }
}

bool PresetManagerComponent::presetNameIsValid(const juce::String& presetName)
{
    if (presetName.isEmpty()) return false;

    if (presetName.containsAnyOf("# @ , ; : < > * ^ | ? / \\")) return false;

    if (presetManagerData.defaultPresetDirectory.getChildFile(presetName + "." + presetManagerData.presetFileExtension).getFullPathName().length() > 255) return false;

    return true;
}
