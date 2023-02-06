/*
  ==============================================================================

    SidePanelHeader.h

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../Assets/ColorPalette.h"

//==============================================================================
/*
*/
class SidePanelHeader  : public juce::Component
{
public:
    SidePanelHeader(const juce::String& titleText);
    ~SidePanelHeader() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setHomeButtonClicked(std::function<void()> callback);
    void setSettingButtonClicked(std::function<void()> callback);

private:
    juce::Label m_titleLabel;
    juce::ShapeButton m_homeButton{ "Home", juce::Colours::transparentBlack, juce::Colours::transparentBlack, juce::Colours::transparentBlack }, m_settingsButton{ "Settings", juce::Colours::transparentBlack, juce::Colours::transparentBlack, juce::Colours::transparentBlack };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SidePanelHeader)
};
