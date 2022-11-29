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
    CustomSliderWithLabel(juce::String name, juce::String suffix = "", const bool isVertical = true, const int numDecimals = 1);
    ~CustomSliderWithLabel() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    juce::Slider& getSlider() { return slider; }

    void applyBypassedColorPalette(const bool bypassed);

    void setValueLabelFont(juce::Font& f);  // Se puede obtener de aqui el tamaño (getHeight).
    void setNameLabelFont(juce::Font& f);

private:
    bool isVertical = true;
    int numDecimals = 1;
    float valueLabelFontHeight{ 18.f }; // Parametrizar y obtener del font importado
    float nameLabelFontHeight{ 14.f };

    void setupSlider();
    void setupValueLabel();
    void setupNameLabel();

    void updateTrackColour();   // Si se usa gradiente. Si no, no hace falta
    void updateValueLabel();

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
