/*
  ==============================================================================

    ScopeView.h
    Clase ScopeView -> Hereda de juce::Component
        - Vista SCOPE -> Visualizador de forma de onda (osciloscopio)

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Assets/ColorPalette.h"
#include "../Assets/CustomLookAndFeel.h"
#include "../Source/PluginProcessor.h"
#include "../Components/ScopeComponent.h"

//==============================================================================
/*
*/
class ScopeView : public juce::Component, virtual CustomLookAndFeel
{
public:
    ScopeView(SinTAudioProcessor& audioProcessor);
    ~ScopeView() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::String viewTitle = "Waveform Visualizer";

    ScopeComponent scopeComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScopeView)
};
