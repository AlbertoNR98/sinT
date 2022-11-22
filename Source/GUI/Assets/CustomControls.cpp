/*
  ==============================================================================

    CustomControls.cpp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CustomControls.h"

//==============================================================================
CustomSliderWithLabel::CustomSliderWithLabel(juce::String name, juce::String suffix, const bool isVertical, const int numDecimals)
{
    this->isVertical = isVertical;
    this->numDecimals = numDecimals;
    if (suffix.isNotEmpty()) this->suffix = " " + suffix;

    setupSlider();
    addAndMakeVisible(slider);

    valueLabel.setFont(valueLabelFontHeight);
    valueLabel.setText(slider.getTextFromValue(slider.getValue()) + this->suffix, juce::dontSendNotification);
    //valueLabel.setJustificationType(juce::Justification::centred);
    valueLabel.setJustificationType(juce::Justification::centredBottom);
    addAndMakeVisible(valueLabel);

    nameLabel.setFont(nameLabelFontHeight);
    nameLabel.setText(name, juce::dontSendNotification);
    //nameLabel.setJustificationType(juce::Justification::centred);
    nameLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(nameLabel);
}

CustomSliderWithLabel::~CustomSliderWithLabel()
{
}

void CustomSliderWithLabel::paint(juce::Graphics& g)
{  
    /*
    // Para Debug
    if (isVertical)
    {
        g.setColour(juce::Colours::red);
        g.drawRect(0, 0, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.80);

        g.setColour(juce::Colours::yellow);
        g.drawRect(0, getLocalBounds().getHeight() * 0.80, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.10);

        g.setColour(juce::Colours::purple);
        g.drawRect(0, getLocalBounds().getHeight() * 0.90, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.10);
    }
    else
    {
        g.setColour(juce::Colours::red);
        g.drawRect(0, 0, getLocalBounds().getWidth() * 0.35, getLocalBounds().getHeight() * 0.5);

        g.setColour(juce::Colours::yellow);
        g.drawRect(0, getLocalBounds().getHeight() * 0.5, getLocalBounds().getWidth() * 0.35, getLocalBounds().getHeight() * 0.5);

        g.setColour(juce::Colours::purple);
        g.drawRect(getLocalBounds().getWidth() * 0.35, 0, getLocalBounds().getWidth() * 0.65, getLocalBounds().getHeight());
    }
    */
}

void CustomSliderWithLabel::resized()
{
    auto localBounds = getLocalBounds();

    if (isVertical)
    {
        slider.setBounds(0, 0, localBounds.getWidth(), localBounds.getHeight() * 0.80);
        valueLabel.setBounds(0, localBounds.getHeight() * 0.80, localBounds.getWidth(), localBounds.getHeight() * 0.10);
        nameLabel.setBounds(0, localBounds.getHeight() * 0.90, localBounds.getWidth(), localBounds.getHeight() * 0.10);
    } 
    else 
    {
        valueLabel.setBounds(0, 0, localBounds.getWidth() * 0.35, localBounds.getHeight() * 0.5);
        nameLabel.setBounds(0, localBounds.getHeight() * 0.5, localBounds.getWidth() * 0.35, localBounds.getHeight() * 0.5);
        slider.setBounds(localBounds.getWidth() * 0.35, 0, localBounds.getWidth() * 0.65, localBounds.getHeight());
    }
}

void CustomSliderWithLabel::updateValueLabel()
{
    valueLabel.setText(slider.getTextFromValue(slider.getValue()) + suffix, juce::dontSendNotification);
}

void CustomSliderWithLabel::setupSlider()
{
    if (isVertical)
    {
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    }
    else 
    {
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    }

    slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    slider.setNumDecimalPlacesToDisplay(numDecimals);

    slider.onValueChange = [this] { 
        updateValueLabel(); 
        //updateTrackColour(); 
    };  // Se ejecuta cuando cambia el valor del slider
}

void CustomSliderWithLabel::applyColorPalette(const bool bypassed)
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