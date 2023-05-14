/*
  ==============================================================================

    SidePanelList.cpp
    Metodos de SidePanelList

  ==============================================================================
*/

#include "SidePanelList.h"

//==============================================================================
SidePanelList::SidePanelList()
{
    setOpaque(true);
    addAndMakeVisible(panelEntries);
    panelEntries.setModel(this);
}

SidePanelList::~SidePanelList()
{
}

void SidePanelList::paint (juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::SidePanel::backgroundColour));
}

void SidePanelList::resized()
{
    panelEntries.setBounds(getLocalBounds());
    panelEntries.setColour(juce::ListBox::ColourIds::backgroundColourId, ColorPalette::airun);
    panelEntries.setRowHeight(getLocalBounds().getHeight() / viewsList.size());
}

void SidePanelList::paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected)
{
    if (rowNumber < 0 || rowNumber >= getNumRows())
        return;

    g.setFont(40.0f);

    juce::Rectangle<int> bounds(0, 0, width, height);
    auto textColour = findColour(juce::Label::textColourId);
    g.setColour(textColour.withAlpha(0.4f));

    if (rowNumber == 0)
        g.fillRect(bounds.removeFromTop(2).reduced(10, 0));

    g.fillRect(bounds.removeFromBottom(2).reduced(10, 0));

    if (rowIsSelected)
    {
        g.setColour(findColour(juce::TextEditor::highlightColourId).withAlpha(0.25f));
        g.fillRect(bounds);
        textColour = ColorPalette::monwhite;
        g.setFont(48.f);
    }

    g.setColour(textColour);
    g.drawFittedText(viewsList[rowNumber], bounds, juce::Justification::centred, 1);
}

void SidePanelList::addEntry(const juce::String& entry)
{
    panelEntries.deselectAllRows();
    viewsList.add(entry);
    panelEntries.updateContent();
}

int SidePanelList::getNumRows()
{
    return viewsList.size();
}

void SidePanelList::selectedRowsChanged(int row)
{
    if (row < 0)
        return;
    clickedEntryCallback(row);
}

void SidePanelList::setEntrySelectionCallback(std::function<void(int)> callback)
{

    clickedEntryCallback = callback;
}
