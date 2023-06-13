/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SinTAudioProcessorEditor::SinTAudioProcessorEditor(SinTAudioProcessor& p)
    : AudioProcessorEditor(&p), 
      audioProcessor(p),
      mainComponent(audioProcessor)
{
    const Rectangle<int> screenArea = Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea;

    // Font
    const auto customFontBold = juce::Typeface::createSystemTypefaceFor(BinaryData::CustomFontBold_ttf, BinaryData::CustomFontBold_ttfSize);
    juce::LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypeface(customFontBold);

    setSize(1024, 576); //Default size

    addAndMakeVisible(mainComponent);

#if !JUCE_STANDALONE_FILTER_WINDOW_USE_KIOSK_MODE
    setResizable(true, false);
    setResizeLimits(1024, 576, screenArea.getWidth(), screenArea.getHeight());
#endif
}

SinTAudioProcessorEditor::~SinTAudioProcessorEditor()
{
}

//==============================================================================
void SinTAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(ColorPalette::basegray);
}

void SinTAudioProcessorEditor::resized()
{
    mainComponent.setBounds(0, 0, getWidth(), getHeight());
}
