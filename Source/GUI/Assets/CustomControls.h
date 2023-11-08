/*
  ==============================================================================

    CustomControls.h
    Fichero con los diferentes controles customizados

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ColorPalette.h"

// Slider con nombre y valor
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
    SliderStyle& getSliderStyle() { return sliderStyle; }

    void applyBypassedColorPalette(const bool bypassed);

private:
    SliderStyle sliderStyle = Vertical;
    int numDecimals = 1;
    float valueLabelFontHeight{ 21.f };
    float nameLabelFontHeight{ 16.f };

    void setupSlider();
    void updateValueLabel();

    juce::Slider slider;
    juce::Label valueLabel;
    juce::Label nameLabel;

    juce::String suffix = "";

    class CustomSliderWithLabelLnF : public juce::LookAndFeel_V4
    {
    public:
        CustomSliderWithLabelLnF(float ratio = 0.5) { fontLabelHeightRatio = ratio; }

        float getfontLabelHeightRatio() { return fontLabelHeightRatio; }
        void setfontLabelHeightRatio(float ratio) { if (ratio >= 0.f && ratio <= 1.f) fontLabelHeightRatio = ratio; }

        virtual void drawLabel(juce::Graphics& g, juce::Label& label) override;

    private:
        float fontLabelHeightRatio = 0.5;

    } cslValueLabelLnF, cslNameLabelLnF;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomSliderWithLabel)
};

// Boton de bypass
class CustomBypassButton : public juce::ToggleButton
{
public: 
    CustomBypassButton(){ setLookAndFeel(&bypassButtonLnF); };
    ~CustomBypassButton() { setLookAndFeel(nullptr); };

private:
    class BypassButtonLnF : public juce::LookAndFeel_V4
    {
        virtual void drawToggleButton(juce::Graphics& g, juce::ToggleButton& toggleButton, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    } bypassButtonLnF;
};
