/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"
#include "GUI/Components/Base/MainComponent.h"
#include "GUI/Components/MainControlComponent.h"
#include "GUI/Components/ADSRComponent.h"
#include "GUI/Components/OscillatorComponent.h"
#include "GUI/Components/FilterComponent.h"
#include "GUI/Components/LFOComponent.h"
#include "GUI/Components/DistortionComponent.h"
#include "GUI/Components/ChorusComponent.h"
#include "GUI/Components/DelayComponent.h"
#include "GUI/Components/ReverbComponent.h"
#include "GUI/Components/MeterComponent.h"

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

    MainComponent mainComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SinTAudioProcessorEditor)
};
