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
#include "GUI/LFOComponent.h"

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
    
    juce::Slider mainGainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mainGainAttachment;

    OscillatorComponent osc1Component;
    OscillatorComponent osc2Component;
    ADSRComponent ampAdsrComponent;
    ADSRComponent filterAdsrComponent;
    FilterComponent filterComponent;
    LFOComponent lfoComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SinTAudioProcessorEditor)
};
