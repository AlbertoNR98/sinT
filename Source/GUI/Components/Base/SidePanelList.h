/*
  ==============================================================================

    SidePanelList.h
    Created: 20 Oct 2022 5:43:23pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SidePanelList  : public juce::Component, juce::ListBoxModel
{
public:
    SidePanelList();
    ~SidePanelList() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) override;
    int getNumRows() override;
    juce::ListBox& getEntries() { return m_entries; }
    void addEntry(const juce::String& entry);
    void selectedRowsChanged(int row) override;
    void setEntrySelectionCallback(std::function<void(int)> callback);

private:
    juce::ListBox m_entries;
    juce::StringArray m_sidePanelEntries;
    std::function<void(int)> m_callback;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SidePanelList)
};
