/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SinTAudioProcessorEditor::SinTAudioProcessorEditor (SinTAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), adsrComponent(audioProcessor.apvts)
{
    setSize (600, 400); // Cambiar

    osc1SelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "OSC1", osc1Selector);
    
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
    // adsrComponent.setBounds(getLocalBounds());
    adsrComponent.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
}

