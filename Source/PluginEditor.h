/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/MainControlComponent.h"
#include "GUI/ADSRComponent.h"
#include "GUI/OscillatorComponent.h"
#include "GUI/FilterComponent.h"
#include "GUI/LFOComponent.h"
#include "GUI/DistortionComponent.h"
#include "GUI/ChorusComponent.h"
#include "GUI/DelayComponent.h"
#include "GUI/ReverbComponent.h"
#include "GUI/MeterComponent.h"

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

    MainControlComponent mainControlComponent;
    OscillatorComponent osc1Component;
    OscillatorComponent osc2Component;
    ADSRComponent ampAdsrComponent;
    ADSRComponent filterAdsrComponent;
    FilterComponent filterComponent;
    LFOComponent lfoComponent;
    DistortionComponent distortionComponent;
    ChorusComponent chorusComponent;
    DelayComponent delayComponent;
    ReverbComponent reverbComponent;

    MeterComponent meterComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SinTAudioProcessorEditor)
};
