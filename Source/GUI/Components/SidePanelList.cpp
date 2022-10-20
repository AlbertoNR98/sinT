/*
  ==============================================================================

    SidePanelList.cpp
    Created: 20 Oct 2022 5:43:23pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#include <JuceHeader.h>

#include "SidePanelList.h"

//==============================================================================
SidePanelList::SidePanelList()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setOpaque(true);
    addAndMakeVisible(m_entries);
    m_entries.setModel(this);
    //m_entries.setRowHeight(40);
    m_entries.setRowHeight(108);
}

SidePanelList::~SidePanelList()
{
}

void SidePanelList::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.fillAll(getLookAndFeel().findColour(juce::SidePanel::backgroundColour));   // clear the background
}

void SidePanelList::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    m_entries.setBounds(getLocalBounds());
    m_entries.setColour(juce::ListBox::ColourIds::backgroundColourId, juce::Colours::orange);
    m_entries.setColour(juce::ListBox::ColourIds::outlineColourId, juce::Colours::aquamarine);
}

void SidePanelList::paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected)
{
    if (rowNumber < 0 || rowNumber >= getNumRows())
        return;

    g.setFont(30.0f);

    juce::Rectangle<int> bounds(0, 0, width, height);
    auto textColour = findColour(juce::Label::textColourId);
    g.setColour(textColour.withAlpha(0.4f));

    if (rowNumber == 0)
        g.fillRect(bounds.removeFromTop(2).reduced(10, 0));

    g.fillRect(bounds.removeFromBottom(2).reduced(10, 0));

    if (rowIsSelected)
    {
        g.setColour(findColour(juce::TextEditor::highlightColourId).withAlpha(0.4f));
        g.fillRect(bounds);
        textColour = findColour(juce::TextEditor::highlightedTextColourId);
    }

    g.setColour(textColour);
    g.drawFittedText(m_sidePanelEntries[rowNumber], bounds, juce::Justification::centred, 1);
}

void SidePanelList::addEntry(const juce::String& entry)
{
    m_entries.deselectAllRows();
    m_sidePanelEntries.add(entry);
    m_entries.updateContent();
}

int SidePanelList::getNumRows()
{
    return m_sidePanelEntries.size();
}

void SidePanelList::selectedRowsChanged(int row)
{
    if (row < 0)
        return;
    m_callback(row);
}

void SidePanelList::setEntrySelectionCallback(std::function<void(int)> callback)
{
    m_callback = callback;
}
