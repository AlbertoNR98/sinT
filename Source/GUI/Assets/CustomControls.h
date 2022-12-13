/*
  ==============================================================================

    CustomControls.h
    Fichero con los diferentes controles customizados

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ColorPalette.h"

class CustomSliderWithLabel : public juce::Component
{
public:
    enum SliderStyle
    {
        Vertical,
        Horizontal,
        HorizontalCompact
    };

    CustomSliderWithLabel(juce::String name, juce::String suffix = "", SliderStyle sliderStyle = Vertical, const int numDecimals = 1);
    ~CustomSliderWithLabel() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    juce::Slider& getSlider() { return slider; }

    void applyBypassedColorPalette(const bool bypassed);
private:
    SliderStyle sliderStyle = Vertical;
    int numDecimals = 1;
    float valueLabelFontHeight{ 18.f };
    float nameLabelFontHeight{ 14.f };

    void setupSlider();
    void updateValueLabel();

    void updateTrackColour();   // Si se usa gradiente. Si no, no hace falta

    juce::Slider slider;
    juce::Label valueLabel;
    juce::Label nameLabel;

    juce::String suffix = "";

    //juce::ColourGradient sliderTrackColourGradient;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomSliderWithLabel)
};


//TO-DO -> ComboBox, ToggleButton y Knob personalizados

class CustomToggleButton
{
    //Nota: Si solo se usa para bypass, cambiar nombre
    
    //SpectrumEQ -> Ver herencia y como se hizo

    //Nota: Ver boton de sidepanel -> NavbarComponent -> Ver si compensa hacer una variante (para portamento) o si con el de bypass vale
};

class CustomComboBox
{
   
};

class CustomKnob
{

};
