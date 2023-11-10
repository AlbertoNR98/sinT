/*
  ==============================================================================

    MainComponent.h
    Clase MainComponent -> Hereda de juce::Component
        - Sobre este component se muestran la barra superior y el component que muestran el panel lateral y las vistas

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ContainerComponent.h"
#include "NavbarComponent.h"
#include "../Source/PluginProcessor.h"
#include "../../Assets/ColorPalette.h"

//==============================================================================
/*
*/
class MainComponent  : public juce::Component
{
public:
    MainComponent(SinTAudioProcessor& audioProcessor);
    ~MainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    NavbarComponent navbarComponent;
    ContainerComponent containerComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
