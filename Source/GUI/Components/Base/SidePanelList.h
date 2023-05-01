/*
  ==============================================================================

    SidePanelList.h
    Clase SidePanelList -> Hereda de juce::Component
        - Lista de vistas del panel lateral
        - Permite seleccionar la vista que se quiera mostrar

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../Assets/ColorPalette.h"

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
    juce::ListBox& getEntries() { return panelEntries; }
    void addEntry(const juce::String& entry);
    void selectedRowsChanged(int row) override;
    void setEntrySelectionCallback(std::function<void(int)> callback);

private:
    juce::ListBox panelEntries;
    juce::StringArray viewsList;
    std::function<void(int)> clickedEntryCallback;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SidePanelList)
};
