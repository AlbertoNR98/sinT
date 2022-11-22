/*
  ==============================================================================

    NavbarComponent.h
    Created: 20 Oct 2022 5:40:57pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../Source/PluginProcessor.h"
#include "../Source/ParamsIDList.h"

#include "ContainerComponent.h"

#include "../MeterComponent.h"
#include "../MainControlComponent.h"

#include "../../Assets/ColorPalette.h"

//==============================================================================
/*
*/

// Boton para desplegar SidePanel -> Actua sobre elementos de ContainerComponent
// Medidor de ganancia -> Hace uso de metodos de AudioProcessor
// Control de ganancia y portamento -> Usa APVTS -> Adaptar MainControlComponent
// Boton de menu de opciones -> Despliega en container el menu de opciones -> Opcional
// Menu de presets
// Info del PC (uso CPU, etc) -> Opcional

class NavbarComponent  : public juce::Component, public juce::Button::Listener
{
public:
    NavbarComponent(SinTAudioProcessor& audioProcessor, ContainerComponent& c);
    ~NavbarComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button*) override;

private:
    juce::TextButton showSidePanel;
    juce::ShapeButton settingsButton;
    MeterComponent gainMeter;
    MainControlComponent mainControl;

    ContainerComponent& containerComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NavbarComponent)
};
