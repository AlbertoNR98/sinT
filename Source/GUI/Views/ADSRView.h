/*
  ==============================================================================

    ADSRView.h
    Clase ADSRView -> Hereda de juce::Component
        - Vista ADSR

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Assets/ColorPalette.h"
#include "../Assets/CustomLookAndFeel.h"
#include "../Components/ADSRComponent.h"

//==============================================================================
/*
*/
class ADSRView : public juce::Component, virtual CustomLookAndFeel
{
public:
    ADSRView(juce::AudioProcessorValueTreeState& apvts,
        juce::String attackIdAmp, juce::String decayIdAmp, juce::String sustainIdAmp, juce::String releaseIdAmp,
        juce::String attackIdFilter, juce::String decayIdFilter, juce::String sustainIdFilter, juce::String releaseIdFilter);
    ~ADSRView() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::String viewTitle = "ADSR Envelopes";

    ADSRComponent filterAdsrComponent, ampAdsrComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRView)
};
