/*
  ==============================================================================

    MeterComponent.h
    Clase MeterComponent -> Hereda de juce::Component
        - Parte de la UI relacionada con el medidor de ganancia de salida

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class MeterComponent  : public juce::Component, public juce::Timer
{
public:
    MeterComponent(std::function<std::pair<float, float>()>&& valueFunction);
    ~MeterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void timerCallback() override;

    void setLevels(const std::pair<float, float> newRmsLevels) { rmsLevels = newRmsLevels; }
    void setLeftLevel(const float newRmsLevel) { rmsLevels.first = newRmsLevel; }
    void setRightLevel(const float newRmsLevel) { rmsLevels.second = newRmsLevel; }

private:
    std::pair<float, float> rmsLevels{ -60.0f, -60.0f };
    std::function<std::pair<float, float>()> getRmsValues;  // Puntero a funcion que devuelve los valores de RMS desde audioProcessor

    juce::Rectangle<float> rmsMeterLeftChannel, rmsMeterRightChannel;
    juce::ColourGradient leftGradient, rightGradient;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeterComponent)
};
