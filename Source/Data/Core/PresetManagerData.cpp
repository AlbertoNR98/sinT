/*
  ==============================================================================

    PresetManagerData.cpp

  ==============================================================================
*/

#include "PresetManagerData.h"

const juce::File PresetManagerData::defaultPresetDirectory {
    juce::File::getSpecialLocation(juce::File::SpecialLocationType::userHomeDirectory)
        .getChildFile(ProjectInfo::projectName)
		.getChildFile("Presets")};
const juce::String PresetManagerData::presetFileExtension { "presint" };
const juce::String PresetManagerData::presetNameProperty{ "presetName" };

PresetManagerData::PresetManagerData(juce::AudioProcessorValueTreeState& tree) : apvts(tree)
{
    // Crear un directorio para los presets, si no existe ya
	if (!defaultPresetDirectory.exists())
	{
		const auto result = defaultPresetDirectory.createDirectory();
		if (!result) return;
	}

	apvts.state.addListener(this);
	currentPreset.referTo(apvts.state.getPropertyAsValue(presetNameProperty, nullptr));
}

void PresetManagerData::savePreset(const juce::String& presetName)
{
	if (presetName.isEmpty()) return;

	currentPreset.setValue(presetName);
	const auto xmlState = apvts.copyState().createXml();
	const auto presetFile = defaultPresetDirectory.getChildFile(presetName + "." + presetFileExtension);

	if (!xmlState->writeTo(presetFile)) return;
}

void PresetManagerData::deletePreset(const juce::String& presetName)
{
	if (presetName.isEmpty()) return;

	const auto presetFile = defaultPresetDirectory.getChildFile(presetName + "." + presetFileExtension);

	if (!presetFile.existsAsFile() || !presetFile.deleteFile()) return;

	currentPreset.setValue("");
}

void PresetManagerData::loadPreset(const juce::String& presetName)
{
	if (presetName.isEmpty()) return;

	const auto presetFile = defaultPresetDirectory.getChildFile(presetName + "." + presetFileExtension);

	if (!presetFile.existsAsFile()) return;

	juce::XmlDocument xmlDocument = presetFile;
	const auto valueTreeToLoad = juce::ValueTree::fromXml(*xmlDocument.getDocumentElement());

	apvts.replaceState(valueTreeToLoad);
	currentPreset.setValue(presetName);
}

int PresetManagerData::loadPreviousPreset()
{
	const auto allPresets = getAllPresets();

	if (allPresets.isEmpty())
		return -1;

	const auto currentIndex = allPresets.indexOf(currentPreset.toString());
	const auto previousIndex = currentIndex - 1 < 0 ? allPresets.size() - 1 : currentIndex - 1;

	loadPreset(allPresets.getReference(previousIndex));

	return previousIndex;
}

int PresetManagerData::loadNextPreset()
{
	const auto allPresets = getAllPresets();

	if (allPresets.isEmpty())
		return -1;

	const auto currentIndex = allPresets.indexOf(currentPreset.toString());
	const auto nextIndex = currentIndex + 1 > (allPresets.size() - 1) ? 0 : currentIndex + 1;

	loadPreset(allPresets.getReference(nextIndex));

	return nextIndex;
}

juce::String PresetManagerData::getCurrentPreset() const
{
	return currentPreset.toString();
}

juce::StringArray PresetManagerData::getAllPresets() const
{
	juce::StringArray presets;
	const auto fileList = defaultPresetDirectory.findChildFiles(
		juce::File::TypesOfFileToFind::findFiles, false, "*." + presetFileExtension);

	for (const auto& file : fileList)
	{
		presets.add(file.getFileNameWithoutExtension());
	}

	return presets;
}

void PresetManagerData::valueTreeRedirected(juce::ValueTree& valueTreeChanged)
{
	currentPreset.referTo(valueTreeChanged.getPropertyAsValue(presetNameProperty, nullptr));
}