/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SinTAudioProcessorEditor::SinTAudioProcessorEditor (SinTAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc1Component(audioProcessor.apvts, "OSC1WF", "OSC1GAIN"), osc2Component(audioProcessor.apvts, "OSC2WF", "OSC2GAIN"), adsrComponent(audioProcessor.apvts)
{
    setSize (600, 400); // Cambiar
    
    addAndMakeVisible(osc1Component);
    addAndMakeVisible(osc2Component);
    addAndMakeVisible(adsrComponent);
}

SinTAudioProcessorEditor::~SinTAudioProcessorEditor()
{
}

//==============================================================================
void SinTAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void SinTAudioProcessorEditor::resized()
{
    osc1Component.setBounds(0, 0, getWidth() / 2, getHeight() / 2);
    osc2Component.setBounds(0, getHeight() / 2, getWidth() / 2, getHeight() / 2);
    adsrComponent.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
}

