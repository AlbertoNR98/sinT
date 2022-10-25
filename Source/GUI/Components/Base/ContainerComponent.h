/*
  ==============================================================================

    ContainerComponent.h
    Created: 20 Oct 2022 5:41:13pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "SidePanelHeader.h"
#include "SidePanelList.h"

#include "../../Views/HomeView.h"
#include "../../Views/OscView.h"
//#include "../../Views/FilterView.h"  -> TO-DO

constexpr int OSC_VIEW = 0;
constexpr int FILTER_VIEW = 1;
constexpr int ADSR_VIEW = 2;
constexpr int FX_VIEW = 3;
constexpr int HOME_VIEW = 4;

//==============================================================================
/*
*/
class ContainerComponent  : public juce::Component
{
public:
    ContainerComponent(juce::AudioProcessorValueTreeState& apvts);
    ~ContainerComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setView(const int);

    juce::SidePanel& getSidePanel() { return sidePanel; }
    void setShowingSidePanel(bool s) { showingSidePanel = s; }
    bool isShowingSidePanel() { return showingSidePanel; }

private:
    void homeButtonClicked();
    void settingsButtonClicked();
    void listEntryClicked(int index);

    bool showingSidePanel = true;
    int sidePanelWidth = 150;
    juce::SidePanel sidePanel{ "", sidePanelWidth, true, nullptr, false };

    std::unique_ptr<juce::Component> contentComponent;

    juce::AudioProcessorValueTreeState& valueTree;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ContainerComponent)
};
