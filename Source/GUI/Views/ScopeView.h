/*
  ==============================================================================

    ScopeView.h
    Clase ScopeView -> Hereda de juce::Component
        - Vista SCOPE

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Assets/ColorPalette.h"
#include "../Source/PluginProcessor.h"
#include "../Components/ScopeComponent.h"

//==============================================================================
/*
*/
class ScopeView  : public juce::Component
{
public:
    ScopeView(SinTAudioProcessor& audioProcessor);
    ~ScopeView() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::String viewTitle = "Wave scope";

    ScopeComponent scopeComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScopeView)
};
