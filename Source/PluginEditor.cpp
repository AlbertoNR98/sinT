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
      mainControlComponent(audioProcessor.apvts, "MAINGAIN", "PORTAMENTO"),
      osc1Component(audioProcessor.apvts, "OSC1WF", "OSC1GAINDB", "OSC1PITCH", "OSC1FMFREQ", "OSC1FMDEPTH"),
      osc2Component(audioProcessor.apvts, "OSC2WF", "OSC2GAINDB", "OSC2PITCH", "OSC2FMFREQ", "OSC2FMDEPTH"),
      ampAdsrComponent(audioProcessor.apvts, "AMPADSRATTACK", "AMPADSRDECAY", "AMPADSRSUSTAIN", "AMPADSRRELEASE"),
      filterAdsrComponent(audioProcessor.apvts, "FILTERADSRATTACK", "FILTERADSRDECAY", "FILTERADSRSUSTAIN", "FILTERADSRRELEASE"),
      filterComponent(audioProcessor.apvts, "FILTERMODE", "FILTERCUTOFFFREQ", "FILTERRESONANCE"),
      lfoComponent(audioProcessor.apvts, "LFOFREQ", "LFODEPTH"),
      distortionComponent(audioProcessor.apvts, "DISTORTIONDRIVE", "DISTORTIONRANGE", "DISTORTIONBLEND"),
      chorusComponent(audioProcessor.apvts, "CHORUSRATE", "CHORUSDEPTH", "CHORUSCENTREDELAY", "CHORUSFEEDBACK", "CHORUSMIX"),
      delayComponent(audioProcessor.apvts, "DELAYTIMEMS", "DELAYFEEDBACK"),
      reverbComponent(audioProcessor.apvts, "REVERBROOMSIZE", "REVERBWIDTH", "REVERBDAMPING", "REVERBFREEZEMODE", "REVERBDRYLEVEL", "REVERBWETLEVEL"),
      meterComponent([&]()->std::pair<float, float> { return audioProcessor.getMainGainMeterRmsValues(); })
{
    // Nota: Al constructor de meterComponent se le pasa una funcion lambda que devuelve los valores de RMS utilizando la funcion realizada para ello en audioProcessor. 
    // MeterComponent apunta a dicha funcion.

    addAndMakeVisible(mainControlComponent);
    addAndMakeVisible(osc1Component);
    addAndMakeVisible(osc2Component);
    addAndMakeVisible(ampAdsrComponent);
    //addAndMakeVisible(filterAdsrComponent);
    //addAndMakeVisible(filterComponent);
    addAndMakeVisible(distortionComponent);
    addAndMakeVisible(chorusComponent);
    //addAndMakeVisible(delayComponent);
    //addAndMakeVisible(lfoComponent);
    addAndMakeVisible(reverbComponent);
    addAndMakeVisible(meterComponent);

    setSize(1200, 544); // 600 - 32 (barra RPi OS) - 24 (barra plugin)
    //setSize(1400, 600);
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
    /*
    mainControlComponent.setBounds(0, 0, getWidth() / 3, 30);
    osc1Component.setBounds(0, 30, getWidth() / 3, (getHeight() / 2) - 30);
    osc2Component.setBounds(0, getHeight() / 2, getWidth() / 3, getHeight() / 2);
    ampAdsrComponent.setBounds(getWidth() / 3, 0, getWidth() / 3, getHeight() / 2);
    //filterAdsrComponent.setBounds(2 * getWidth() / 3, 0, getWidth() / 3, getHeight() / 2);
    //filterComponent.setBounds(2 * getWidth() / 3, getHeight() / 2, getWidth() / 3, getHeight() / 2);
    //lfoComponent.setBounds(getWidth() / 3, getHeight() / 2, getWidth() / 3, getHeight() / 2);
    //distortionComponent.setBounds(getWidth() / 3, getHeight() / 2, getWidth() / 3, getHeight() / 2);
    delayComponent.setBounds(getWidth() / 3, getHeight() / 2, getWidth() / 3, getHeight() / 2);
    //reverbComponent.setBounds(getWidth() / 3, getHeight() / 2, getWidth() / 3, getHeight() / 2);
    //reverbComponent.setBounds(2 * getWidth() / 3, 0, getWidth() / 3, getHeight() / 2);
    chorusComponent.setBounds(2 * getWidth() / 3, 0, getWidth() / 3, getHeight() / 2);
    meterComponent.setBounds(2 * getWidth() / 3, getHeight() / 2, getWidth() / 3, getHeight() / 2);
    */

    osc1Component.setBounds(0, 0, getWidth() / 4, getHeight() / 3);
    osc2Component.setBounds(getWidth() / 4, 0, getWidth() / 4, getHeight() / 3);
    lfoComponent.setBounds(2 * getWidth() / 4, 0, getWidth() / 4, getHeight() / 3);
    ampAdsrComponent.setBounds(3 * getWidth() / 4, 0, getWidth() / 4, getHeight() / 3);

    distortionComponent.setBounds(0, getHeight() / 3, getWidth() / 4, getHeight() / 3);
    chorusComponent.setBounds(getWidth() / 4, getHeight() / 3, getWidth() / 4, getHeight() / 3);
    delayComponent.setBounds(2 * getWidth() / 4, getHeight() / 3, getWidth() / 4, getHeight() / 3);
    reverbComponent.setBounds(3 * getWidth() / 4, getHeight() / 3, getWidth() / 4, getHeight() / 3);

    filterComponent.setBounds(0, 2 * getHeight() / 3, getWidth() / 4, getHeight() / 3);
    filterAdsrComponent.setBounds(getWidth() / 4, 2 * getHeight() / 3, getWidth() / 4, getHeight() / 3);
    mainControlComponent.setBounds(2 * getWidth() / 4, 2 * getHeight() / 3, getWidth() / 4, getHeight() / 3);
    meterComponent.setBounds(3 * getWidth() / 4, 2 * getHeight() / 3, getWidth() / 4, getHeight() / 3);
}
