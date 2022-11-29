/*
  ==============================================================================

    ADSRView.cpp
    Created: 29 Nov 2022 6:53:19pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRView.h"

//==============================================================================
ADSRView::ADSRView(juce::AudioProcessorValueTreeState& apvts, 
    juce::String attackIdAmp, juce::String decayIdAmp, juce::String sustainIdAmp, juce::String releaseIdAmp, 
    juce::String attackIdFilter, juce::String decayIdFilter, juce::String sustainIdFilter, juce::String releaseIdFilter) :
    ampAdsrComponent("Amplitude ADSR", apvts, attackIdAmp, decayIdAmp, sustainIdAmp, releaseIdAmp), 
    filterAdsrComponent("Filter ADSR", apvts, attackIdFilter, decayIdFilter, sustainIdFilter, releaseIdFilter)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(ampAdsrComponent);
    addAndMakeVisible(filterAdsrComponent);
}

ADSRView::~ADSRView()
{
}

void ADSRView::paint (juce::Graphics& g)
{
    g.fillAll(ColorPalette::darkgray);

    g.setColour(juce::Colours::wheat);
    g.setFont(44.0f);

    auto padding = 16;

    auto elementsBounds = getLocalBounds().reduced(padding);
    auto textBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() / 8);
    //g.drawRoundedRectangle(textBounds.toFloat(), 10.0f, 2.0f);
    //g.drawRect(textBounds, 5);
    g.drawFittedText(viewTitle, textBounds, juce::Justification::centred, true);

    elementsBounds.setPosition(juce::Point<int>(elementsBounds.getPosition().getX(), textBounds.getBottom() + padding));
    elementsBounds.setSize(elementsBounds.getWidth(), elementsBounds.getHeight() - textBounds.getHeight() - padding);
}

void ADSRView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    auto padding = 16;

    auto elementsBounds = getLocalBounds().reduced(padding);

    auto textBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() / 8);

    elementsBounds.setPosition(juce::Point<int>(elementsBounds.getPosition().getX(), textBounds.getBottom() + padding));
    elementsBounds.setSize(elementsBounds.getWidth(), elementsBounds.getHeight() - textBounds.getHeight() - padding);

    auto ampAdsrBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), (elementsBounds.getWidth() / 2) - (padding / 2), elementsBounds.getHeight());
    auto filterAdsrBounds = juce::Rectangle<int>(elementsBounds.getCentre().getX() + (padding / 2), elementsBounds.getPosition().getY(), (elementsBounds.getWidth() / 2) - (padding / 2), elementsBounds.getHeight());

    ampAdsrComponent.setBounds(ampAdsrBounds);
    filterAdsrComponent.setBounds(filterAdsrBounds);
}
