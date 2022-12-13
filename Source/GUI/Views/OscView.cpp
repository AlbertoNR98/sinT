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
    juce::String bypassedId1, juce::String waveformSelectorId1, juce::String oscGainId1, juce::String oscPitchId1, juce::String fmFreqId1, juce::String fmDepthId1,
    juce::String bypassedId2, juce::String waveformSelectorId2, juce::String oscGainId2, juce::String oscPitchId2, juce::String fmFreqId2, juce::String fmDepthId2) :
    osc1Component("Oscillator 1", apvts, bypassedId1, waveformSelectorId1, oscGainId1, oscPitchId1, fmFreqId1, fmDepthId1),
    osc2Component("Oscillator 2", apvts, bypassedId2, waveformSelectorId2, oscGainId2, oscPitchId2, fmFreqId2, fmDepthId2)
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
    g.setColour(juce::Colours::wheat);
    g.setFont(44.0f);

    auto padding = 16;

    auto elementsBounds = getLocalBounds().reduced(padding);
    auto textBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() / 8);
    //g.drawRoundedRectangle(textBounds.toFloat(), 10.0f, 2.0f);
    //g.drawRect(textBounds, 5);
    g.drawFittedText(viewTitle, textBounds, juce::Justification::centred, true);

    //g.setColour(juce::Colours::black);
    elementsBounds.setPosition(juce::Point<int>(elementsBounds.getPosition().getX(), textBounds.getBottom() + padding));
    elementsBounds.setSize(elementsBounds.getWidth(), elementsBounds.getHeight() - textBounds.getHeight() - padding);
    //g.drawRect(elementsBounds, 5);

    //g.setColour(juce::Colours::coral);
    //auto osc1Bounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), (elementsBounds.getWidth() / 2) - (padding / 2), elementsBounds.getHeight());
    //g.drawRoundedRectangle(osc1Bounds.toFloat().reduced(10.0f), 5.0f, 2.0f);
    //g.drawRect(osc1Bounds, 5);

    //g.setColour(juce::Colours::coral);
    //auto osc2Bounds = juce::Rectangle<int>(elementsBounds.getCentre().getX() + (padding / 2), elementsBounds.getPosition().getY(), (elementsBounds.getWidth() / 2) - (padding / 2), elementsBounds.getHeight());
    //g.drawRoundedRectangle(osc2Bounds.toFloat().reduced(10.0f), 5.0f, 2.0f);
    //g.drawRect(osc2Bounds, 5);
}

void OscView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    auto padding = 16;

    auto elementsBounds = getLocalBounds().reduced(padding);

    auto textBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() / 8);

    elementsBounds.setPosition(juce::Point<int>(elementsBounds.getPosition().getX(), textBounds.getBottom() + padding));
    elementsBounds.setSize(elementsBounds.getWidth(), elementsBounds.getHeight() - textBounds.getHeight() - padding);

    auto osc1Bounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), (elementsBounds.getWidth() / 2) - (padding / 2), elementsBounds.getHeight());
    auto osc2Bounds = juce::Rectangle<int>(elementsBounds.getCentre().getX() + (padding / 2), elementsBounds.getPosition().getY(), (elementsBounds.getWidth() / 2) - (padding / 2), elementsBounds.getHeight());

    osc1Component.setBounds(osc1Bounds);
    osc2Component.setBounds(osc2Bounds);
}
