/*
  ==============================================================================

    CustomControls.cpp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CustomControls.h"

//==============================================================================
CustomSliderWithLabel::CustomSliderWithLabel(juce::String name, juce::String suffix, SliderStyle sliderStyle, const int numDecimals)
{
    this->sliderStyle = sliderStyle;
    this->numDecimals = numDecimals;
    if (suffix.isNotEmpty()) this->suffix = " " + suffix;

    setupSlider();
    addAndMakeVisible(slider);

    valueLabel.setFont(valueLabelFontHeight);
    valueLabel.setText(slider.getTextFromValue(slider.getValue()) + this->suffix, juce::dontSendNotification);
    addAndMakeVisible(valueLabel);

    nameLabel.setFont(nameLabelFontHeight);
    nameLabel.setText(name, juce::dontSendNotification);
    addAndMakeVisible(nameLabel);
}

CustomSliderWithLabel::~CustomSliderWithLabel()
{
}

void CustomSliderWithLabel::paint(juce::Graphics& g)
{  
    /*
    // Para debug

    g.setColour(juce::Colours::green);
    g.drawRect(getLocalBounds());

    switch (sliderStyle)
    {
    case Vertical:
        g.setColour(juce::Colours::red);
        g.drawRect(0, 0, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.80);

        g.setColour(juce::Colours::yellow);
        g.drawRect(0, getLocalBounds().getHeight() * 0.80, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.10);

        g.setColour(juce::Colours::purple);
        g.drawRect(0, getLocalBounds().getHeight() * 0.90, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.10);
        break;
    case Horizontal:
        g.setColour(juce::Colours::red);
        g.drawRect(0, 0, getLocalBounds().getWidth() * 0.2, getLocalBounds().getHeight());

        g.setColour(juce::Colours::yellow);
        g.drawRect(getLocalBounds().getWidth() * 0.2, 0, getLocalBounds().getWidth() * 0.15, getLocalBounds().getHeight());

        g.setColour(juce::Colours::purple);
        g.drawRect(getLocalBounds().getWidth() * 0.35, 0, getLocalBounds().getWidth() * 0.65, getLocalBounds().getHeight());
        break;
    case HorizontalCompact:
        g.setColour(juce::Colours::red);
        g.drawRect(0, 0, getLocalBounds().getWidth() * 0.35, getLocalBounds().getHeight() * 0.5);

        g.setColour(juce::Colours::yellow);
        g.drawRect(0, getLocalBounds().getHeight() * 0.5, getLocalBounds().getWidth() * 0.35, getLocalBounds().getHeight() * 0.5);

        g.setColour(juce::Colours::purple);
        g.drawRect(getLocalBounds().getWidth() * 0.35, 0, getLocalBounds().getWidth() * 0.65, getLocalBounds().getHeight());
        break;
    default:
        g.setColour(juce::Colours::red);
        g.drawRect(0, 0, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.80);

        g.setColour(juce::Colours::yellow);
        g.drawRect(0, getLocalBounds().getHeight() * 0.80, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.10);

        g.setColour(juce::Colours::purple);
        g.drawRect(0, getLocalBounds().getHeight() * 0.90, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.10);
        break;
    }
    */
}

void CustomSliderWithLabel::resized()
{
    auto localBounds = getLocalBounds();

    switch (sliderStyle)
    {
    case Vertical:
        slider.setBounds(0, 0, localBounds.getWidth(), localBounds.getHeight() * 0.80);
        valueLabel.setBounds(0, localBounds.getHeight() * 0.80, localBounds.getWidth(), localBounds.getHeight() * 0.10);
        nameLabel.setBounds(0, localBounds.getHeight() * 0.90, localBounds.getWidth(), localBounds.getHeight() * 0.10);
        break;
    case Horizontal:
        nameLabel.setBounds(0, 0, localBounds.getWidth() * 0.2, localBounds.getHeight());
        valueLabel.setBounds(localBounds.getWidth() * 0.2, 0, localBounds.getWidth() * 0.15, localBounds.getHeight());
        slider.setBounds(localBounds.getWidth() * 0.35, 0, localBounds.getWidth() * 0.65, localBounds.getHeight());
        break;
    case HorizontalCompact:
        valueLabel.setBounds(0, 0, localBounds.getWidth() * 0.2, localBounds.getHeight() * 0.5);
        nameLabel.setBounds(0, localBounds.getHeight() * 0.5, localBounds.getWidth() * 0.2, localBounds.getHeight() * 0.5);
        slider.setBounds(localBounds.getWidth() * 0.2, 0, localBounds.getWidth() * 0.8, localBounds.getHeight());
        break;
    default:
        slider.setBounds(0, 0, localBounds.getWidth(), localBounds.getHeight() * 0.80);
        valueLabel.setBounds(0, localBounds.getHeight() * 0.80, localBounds.getWidth(), localBounds.getHeight() * 0.10);
        nameLabel.setBounds(0, localBounds.getHeight() * 0.90, localBounds.getWidth(), localBounds.getHeight() * 0.10);
        break;
    }
}

void CustomSliderWithLabel::updateValueLabel()
{
    valueLabel.setText(slider.getTextFromValue(slider.getValue()) + suffix, juce::dontSendNotification);
}

void CustomSliderWithLabel::setupSlider()
{
    switch (sliderStyle) {
    case Vertical:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        valueLabel.setJustificationType(juce::Justification::centredBottom);
        nameLabel.setJustificationType(juce::Justification::centredTop);
        break;
    case Horizontal:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
        valueLabel.setJustificationType(juce::Justification::centred);
        nameLabel.setJustificationType(juce::Justification::centred);
        break;
    case HorizontalCompact:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
        valueLabel.setJustificationType(juce::Justification::centredBottom);
        nameLabel.setJustificationType(juce::Justification::centredTop);
        break;
    default:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        valueLabel.setJustificationType(juce::Justification::centredBottom);
        nameLabel.setJustificationType(juce::Justification::centredTop);
    }

    slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    slider.setNumDecimalPlacesToDisplay(numDecimals);
    //slider.setVelocityBasedMode(true);
    //slider.setVelocityModeParameters(); -> Hacer pruebas

    slider.onValueChange = [this] { 
        updateValueLabel(); 
        //updateTrackColour(); 
    };  // Se ejecuta cuando cambia el valor del slider
}

void CustomSliderWithLabel::applyBypassedColorPalette(const bool bypassed)
{
    // Nota: Cambiar paleta de colores y cambiar color de letra de los labels
    if (bypassed)
    {
        slider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::red);
        slider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::green);
        slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::white);
    } 
    else 
    {
        slider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::darkviolet);
        slider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::orange);
        slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::cadetblue);
    }
}