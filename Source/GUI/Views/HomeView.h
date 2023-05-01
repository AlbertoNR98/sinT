/*
  ==============================================================================

    HomeView.h
    Clase HomeView -> Hereda de juce::Component
        - Vista HOME -> Pantalla por defecto

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Assets/ColorPalette.h"

//==============================================================================
/*
*/
class HomeView  : public juce::Component
{
public:
    HomeView();
    ~HomeView() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HomeView)
};
