/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SinTAudioProcessorEditor::SinTAudioProcessorEditor (SinTAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc1Component(audioProcessor.apvts, "OSC1WF", "OSC1GAIN"), adsrComponent(audioProcessor.apvts)
{
    setSize (600, 400); // Cambiar
    
    addAndMakeVisible(osc1Component);
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
    osc1Component.setBounds(0, 0, getWidth() / 2, getHeight());
    adsrComponent.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
}

