/*
  ==============================================================================

    SidePanelHeader.h
    Clase SidePanelHeader -> Hereda de juce::Component
        - Parte superior del panel lateral
        - Contiene:
            - Boton de about -> Muestra la vista HOME
            - Boton de settings -> Muestra la vista de settings -> Solo disponible en Kiosk Mode

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
    SidePanelHeader();
    ~SidePanelHeader() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setAboutButtonClicked(std::function<void()> callback);
    void setSettingButtonClicked(std::function<void()> callback);

private:
    juce::TextButton titleAboutButton;
    juce::ShapeButton settingsButton{ "Settings", juce::Colours::transparentBlack, juce::Colours::transparentBlack, juce::Colours::transparentBlack };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SidePanelHeader)
};
