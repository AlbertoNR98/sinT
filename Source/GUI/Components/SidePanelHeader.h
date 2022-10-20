/*
  ==============================================================================

    SidePanelHeader.h
    Created: 20 Oct 2022 5:43:33pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SidePanelHeader  : public juce::Component
{
public:
    SidePanelHeader();
    ~SidePanelHeader() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SidePanelHeader)
};
