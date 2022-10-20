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

#include "../Views/HomeView.h"
//#include "../Views/OscView.h" -> TO-DO
//#include "../Views/FilterView.h"  -> TO-DO

//==============================================================================
/*
*/
class ContainerComponent  : public juce::Component, public juce::Button::Listener
{
public:
    ContainerComponent(juce::AudioProcessorValueTreeState& apvts);
    ~ContainerComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button*) override;

    //void setView(juce::Component*);
    void setView(juce::Component&);
    void clearCurrentView();

    juce::SidePanel& getSidePanel() { return m_sidePanel; }
    void setShowingSidePanel(bool s) { m_showingSidePanel = s; }
    bool isShowingSidePanel() { return m_showingSidePanel; }

    HomeView& getHomeView() { return homeView; }

private:
    void homeButtonClicked();
    void settingsButtonClicked();
    void listEntryClicked(int index);

    juce::TextButton m_invokeSidePanel;
    juce::Label m_sidePanelStatus;

    bool m_showingSidePanel = true; // Variables -> Hacer get
    int m_sidePanelWidth = 150;
    juce::SidePanel m_sidePanel{ "", m_sidePanelWidth, true, nullptr, false };

    //Nuevo 2
    //OscView oscView;
    HomeView homeView;
    //OscView oscView;
    //FilterView filterView;

    juce::Component* comp = &homeView;
    //std::unique_ptr<juce::Component> comp;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ContainerComponent)
};
