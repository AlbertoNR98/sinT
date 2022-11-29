/*
  ==============================================================================

    FilterView.h
    Created: 29 Nov 2022 5:00:16pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//#include "../Components/ContainerComponent.h"

#include "../Assets/ColorPalette.h"
#include "../Components/FilterComponent.h"
#include "../Components/LFOComponent.h"

//==============================================================================
/*
*/
class FilterView  : public juce::Component
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
