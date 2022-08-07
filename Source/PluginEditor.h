/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/ADSRComponent.h"

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
    juce::ComboBox osc1Selector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> osc1SelectorAttachment;

    SinTAudioProcessor& audioProcessor;
    
    ADSRComponent adsrComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SinTAudioProcessorEditor)
};
