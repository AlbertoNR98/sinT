/*
  ==============================================================================

    ContainerComponent.h
    Clase ContainerComponent -> Hereda de juce::Component
        - Sobre este component se muestran las distintas vistas que contienen los controles de cada apartado
        - Tambien contiene el panel lateral

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Source/ParamsIDList.h"
#include "../Source/PluginProcessor.h"
#include "SidePanelHeader.h"
#include "SidePanelList.h"
#include "../../Assets/ColorPalette.h"
#include "../../Views/HomeView.h"
#include "../../Views/SettingsView.h"
#include "../../Views/OscView.h"
#include "../../Views/ADSRView.h"
#include "../../Views/FilterView.h"
#include "../../Views/FXProcessorView.h"
#include "../../Views/ScopeView.h"

//==============================================================================
/*
*/
class ContainerComponent : public juce::Component
{
public:
    enum ViewSelector
    {
        OSC_VIEW,
        ADSR_VIEW,
        FILTER_VIEW,
        FX_VIEW,
        SCOPE_VIEW,
        HOME_VIEW,
        SETTINGS_VIEW
    };

    ContainerComponent(SinTAudioProcessor& audioProcessor);
    ~ContainerComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setView(const int);

    juce::SidePanel& getSidePanel() { return sidePanel; }
    void setShowingSidePanel(bool s) { showingSidePanel = s; }
    bool isShowingSidePanel() { return showingSidePanel; }

private:
    void aboutButtonClicked();
    void settingsButtonClicked();
    void listEntryClicked(int index);

    bool showingSidePanel = true;
    int sidePanelWidth = 150;
    SidePanelList* sidePanelList = new SidePanelList();
    SidePanelHeader* sidePanelHeader = new SidePanelHeader();
    juce::SidePanel sidePanel{ "", sidePanelWidth, true, nullptr, false };

    std::unique_ptr<juce::AlertWindow> aboutDialog;

    std::unique_ptr<juce::Component> contentComponent;

    SinTAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ContainerComponent)
};
