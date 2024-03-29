/*
  ==============================================================================

    NavbarComponent.h
    Clase NavbarComponent -> Hereda de juce::Component
        - Barra superior con:
            - Boton para desplegar SidePanel -> Actua sobre elementos de ContainerComponent
            - Medidor de ganancia -> Hace uso de metodos de AudioProcessor
            - Control de ganancia y portamento -> Usa APVTS -> Adaptar MainControlComponent
            - Menu de presets
       
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Source/PluginProcessor.h"
#include "../Source/ParamsIDList.h"
#include "ContainerComponent.h"
#include "../MeterComponent.h"
#include "../MainControlComponent.h"
#include "../PresetManagerComponent.h"
#include "../../Assets/ColorPalette.h"

//==============================================================================
/*
*/

class NavbarComponent  : public juce::Component, public juce::Button::Listener
{
public:
    NavbarComponent(SinTAudioProcessor& audioProcessor, ContainerComponent& c);
    ~NavbarComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button*) override;

private:
    juce::TextButton showSidePanelButton;

    MeterComponent gainMeter;
    MainControlComponent mainControl;
    PresetManagerComponent presetManager;

    ContainerComponent& containerComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NavbarComponent)
};
