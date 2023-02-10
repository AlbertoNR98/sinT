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
    float valueLabelFontHeight{ 20.f };
    float nameLabelFontHeight{ 16.f };

    void setupSlider();
    void updateValueLabel();

    juce::Slider slider;
    juce::Label valueLabel;
    juce::Label nameLabel;

    juce::String suffix = "";

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomSliderWithLabel)
};

class CustomBypassButton : public juce::ToggleButton
{
public: 
    CustomBypassButton(){ setLookAndFeel(&bypassButtonLnF); };
    ~CustomBypassButton() { setLookAndFeel(nullptr); };

private:
    class BypassButtonLnF : public juce::LookAndFeel_V4
    {
        void drawToggleButton(juce::Graphics& g, juce::ToggleButton& toggleButton, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    } bypassButtonLnF;
};
