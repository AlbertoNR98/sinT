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

    savePresetButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.2f)).reduced(4));
    previousPresetButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.1f)).reduced(4));
    presetListComboBox.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.4f)).reduced(4));
    nextPresetButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.1f)).reduced(4));
    deletePresetButton.setBounds(bounds.reduced(4));
}

void PresetManagerComponent::setupButton(juce::Button& button, const String& buttonText)
{
    button.setButtonText(buttonText);
    addAndMakeVisible(button);
    button.addListener(this);
}

void PresetManagerComponent::setupComboBox(juce::ComboBox& comboBox)
{
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
        fileChooser = std::make_unique<juce::FileChooser>(
            "Save a Preset",
            PresetManagerData::defaultPresetDirectory,
            "*." + PresetManagerData::presetFileExtension
        );

        fileChooser->launchAsync(juce::FileBrowserComponent::saveMode, [&](const juce::FileChooser& chooser) {
            const auto resultFile = chooser.getResult();
            presetManagerData.savePreset(resultFile.getFileNameWithoutExtension());
            loadPresetList();
        });
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
