/*
  ==============================================================================

    OscView.cpp
    Created: 20 Oct 2022 7:56:30pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscView.h"

//==============================================================================
OscView::OscView(juce::AudioProcessorValueTreeState& apvts,
    juce::String waveformSelectorId1, juce::String oscGainId1, juce::String oscPitchId1, juce::String fmFreqId1, juce::String fmDepthId1,
    juce::String waveformSelectorId2, juce::String oscGainId2, juce::String oscPitchId2, juce::String fmFreqId2, juce::String fmDepthId2) :
    osc1Component(apvts, waveformSelectorId1, oscGainId1, oscPitchId1, fmFreqId1, fmDepthId1),
    osc2Component(apvts, waveformSelectorId2, oscGainId2, oscPitchId2, fmFreqId2, fmDepthId2)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(osc1Component);
    addAndMakeVisible(osc2Component);
}

OscView::~OscView()
{
}

void OscView::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    /*
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("OscView", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
    */
    g.fillAll(juce::Colours::cadetblue);
}

void OscView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    osc1Component.setBounds(0, 0, getWidth() / 2, getHeight());
    osc2Component.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
}
