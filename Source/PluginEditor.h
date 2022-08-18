/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/ADSRComponent.h"
#include "GUI/OscillatorComponent.h"
#include "GUI/FilterComponent.h"

//==============================================================================
/**
*/
class SinTAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SinTAudioProcessorEditor (SinTAudioProcessor&);
    ~SinTAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SinTAudioProcessor& audioProcessor;
    
    OscillatorComponent osc1Component;
    OscillatorComponent osc2Component;
    ADSRComponent adsrComponent;
    FilterComponent filterComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SinTAudioProcessorEditor)
};
