/*
  ==============================================================================

    ADSRView.h

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../Assets/ColorPalette.h"
#include "../Components/ADSRComponent.h"

//==============================================================================
/*
*/
class ADSRView  : public juce::Component
{
public:
    ADSRView(juce::AudioProcessorValueTreeState& apvts,
        juce::String attackIdAmp, juce::String decayIdAmp, juce::String sustainIdAmp, juce::String releaseIdAmp,
        juce::String attackIdFilter, juce::String decayIdFilter, juce::String sustainIdFilter, juce::String releaseIdFilter);
    ~ADSRView() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::String viewTitle = "ADSR envelopes";

    ADSRComponent filterAdsrComponent, ampAdsrComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRView)
};
