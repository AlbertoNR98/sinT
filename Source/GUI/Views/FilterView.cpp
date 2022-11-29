/*
  ==============================================================================

    FilterView.cpp
    Created: 29 Nov 2022 5:00:16pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterView.h"

//==============================================================================
FilterView::FilterView(juce::AudioProcessorValueTreeState& apvts, 
    juce::String filterBypassedId, juce::String filterModeSelectorId, juce::String filterCutoffFreqId, juce::String filterResonanceId, 
    juce::String lfoFreqId, juce::String lfoDepthId) :
    filterComponent(apvts, filterBypassedId, filterModeSelectorId, filterCutoffFreqId, filterResonanceId),
    lfoComponent(apvts, lfoFreqId, lfoDepthId)
{
    addAndMakeVisible(filterComponent);
    addAndMakeVisible(lfoComponent);
}

FilterView::~FilterView()
{
}

void FilterView::paint (juce::Graphics& g)
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

    //g.fillAll(juce::Colours::cadetblue);

    g.fillAll(ColorPalette::darkgray);

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

void FilterView::resized()
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

    filterComponent.setBounds(osc1Bounds);
    lfoComponent.setBounds(osc2Bounds);
}
