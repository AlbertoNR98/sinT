/*
  ==============================================================================

    FXProcessorView.cpp
    Created: 29 Nov 2022 7:44:41pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FXProcessorView.h"

//==============================================================================
FXProcessorView::FXProcessorView(juce::AudioProcessorValueTreeState& apvts,
    juce::String distortionBypassed, juce::String distortionDrive, juce::String distortionRange, juce::String distortionBlend,
    juce::String chorusBypassed, juce::String chorusRate, juce::String chorusDepth, juce::String chorusCentreDelay, juce::String chorusFeedback, juce::String chorusMix,
    juce::String delayBypassed, juce::String delayTimeMs, juce::String delayFeedback,
    juce::String reverbBypassed, juce::String reverbRoomSize, juce::String reverbWidth, juce::String reverbDamping, juce::String reverbFreezeMode, juce::String reverbDryLevel, juce::String reverbWetLevel) :
    distortionComponent("Distortion", apvts, distortionBypassed, distortionDrive, distortionRange, distortionBlend),
    chorusComponent("Chorus", apvts, chorusBypassed, chorusRate, chorusDepth, chorusCentreDelay, chorusFeedback, chorusMix),
    delayComponent("Delay", apvts, delayBypassed, delayTimeMs, delayFeedback),
    reverbComponent("Reverb", apvts, reverbBypassed, reverbRoomSize, reverbWidth, reverbDamping, reverbFreezeMode, reverbDryLevel, reverbWetLevel)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(distortionComponent);
    addAndMakeVisible(chorusComponent);
    addAndMakeVisible(delayComponent);
    addAndMakeVisible(reverbComponent);
}

FXProcessorView::~FXProcessorView()
{
}

void FXProcessorView::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

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

}

void FXProcessorView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    auto padding = 16;

    auto elementsBounds = getLocalBounds().reduced(padding);

    auto textBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() / 8);

    elementsBounds.setPosition(juce::Point<int>(elementsBounds.getPosition().getX(), textBounds.getBottom() + padding));
    elementsBounds.setSize(elementsBounds.getWidth(), elementsBounds.getHeight() - textBounds.getHeight() - padding);

    auto distortionBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), (elementsBounds.getWidth() / 2) - (padding / 2), elementsBounds.getHeight() * 0.35);
    auto chorusBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), distortionBounds.getBottom() + padding, (elementsBounds.getWidth() / 2) - (padding / 2), elementsBounds.getHeight() * 0.65);
    auto delayBounds = juce::Rectangle<int>(elementsBounds.getCentre().getX() + (padding / 2), elementsBounds.getPosition().getY(), (elementsBounds.getWidth() / 2) - (padding / 2), elementsBounds.getHeight() * 0.35);
    auto reverbBounds = juce::Rectangle<int>(elementsBounds.getCentre().getX() + (padding / 2), delayBounds.getBottom() + padding, (elementsBounds.getWidth() / 2) - (padding / 2), elementsBounds.getHeight() * 0.65);

    distortionComponent.setBounds(distortionBounds);
    chorusComponent.setBounds(chorusBounds);
    delayComponent.setBounds(delayBounds);
    reverbComponent.setBounds(reverbBounds);
}
