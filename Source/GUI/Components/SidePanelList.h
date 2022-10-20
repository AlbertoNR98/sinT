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
class SidePanelList  : public juce::Component
{
public:
    SidePanelList();
    ~SidePanelList() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SidePanelList)
};
