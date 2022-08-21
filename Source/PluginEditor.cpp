/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SinTAudioProcessorEditor::SinTAudioProcessorEditor (SinTAudioProcessor& p)
    : AudioProcessorEditor (&p), 
      audioProcessor (p), 
      osc1Component(audioProcessor.apvts, "OSC1WF", "OSC1GAINDB", "OSC1PITCH", "OSC1FMFREQ", "OSC1FMDEPTH"),
      osc2Component(audioProcessor.apvts, "OSC2WF", "OSC2GAINDB", "OSC2PITCH", "OSC2FMFREQ", "OSC2FMDEPTH"),
      ampAdsrComponent(audioProcessor.apvts, "AMPADSRATTACK", "AMPADSRDECAY", "AMPADSRSUSTAIN", "AMPADSRRELEASE"),
      filterAdsrComponent(audioProcessor.apvts, "FILTERADSRATTACK", "FILTERADSRDECAY", "FILTERADSRSUSTAIN", "FILTERADSRRELEASE"),
      filterComponent(audioProcessor.apvts, "FILTERMODE", "FILTERCUTOFFFREQ", "FILTERRESONANCE"),
      lfoComponent(audioProcessor.apvts, "LFOFREQ", "LFODEPTH")
{
    setSize (1200, 600); // Cambiar
    
    mainGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(mainGainSlider);
    mainGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "MAINGAIN", mainGainSlider);

    addAndMakeVisible(osc1Component);
    addAndMakeVisible(osc2Component);
    addAndMakeVisible(ampAdsrComponent);
    addAndMakeVisible(filterAdsrComponent);
    addAndMakeVisible(filterComponent);
    addAndMakeVisible(lfoComponent);
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
    mainGainSlider.setBounds(0, 0, getWidth() / 3, 30);
    osc1Component.setBounds(0, 30, getWidth() / 3, (getHeight() / 2) - 30);
    osc2Component.setBounds(0, getHeight() / 2, getWidth() / 3, getHeight() / 2);
    ampAdsrComponent.setBounds(getWidth() / 3, 0, getWidth() / 3, getHeight() / 2);
    filterAdsrComponent.setBounds(2 * getWidth() / 3, 0, getWidth() / 3, getHeight() / 2);
    filterComponent.setBounds(2 * getWidth() / 3, getHeight() / 2, getWidth() / 3, getHeight() / 2);
    lfoComponent.setBounds(getWidth() / 3, getHeight() / 2, getWidth() / 3, getHeight() / 2);
}
