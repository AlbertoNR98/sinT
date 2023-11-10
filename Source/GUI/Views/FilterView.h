/*
  ==============================================================================

    FilterView.h
    Clase FilterView -> Hereda de juce::Component
        - Vista FILTER

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Assets/ColorPalette.h"
#include "../Assets/CustomLookAndFeel.h"
#include "../Components/FilterComponent.h"
#include "../Components/LFOComponent.h"

//==============================================================================
/*
*/
class FilterView : public juce::Component, virtual CustomLookAndFeel
{
public:
    FilterView(juce::AudioProcessorValueTreeState& apvts, 
        juce::String filterBypassedId, juce::String filterModeSelectorId, juce::String filterCutoffFreqId, juce::String filterResonanceId,
        juce::String lfoFreqId, juce::String lfoDepthId);
    ~FilterView() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::String viewTitle = "Filters";

    FilterComponent filterComponent;
    LFOComponent lfoComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterView)
};
