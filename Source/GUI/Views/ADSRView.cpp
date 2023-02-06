/*
  ==============================================================================

    ADSRView.cpp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRView.h"

//==============================================================================
ADSRView::ADSRView(juce::AudioProcessorValueTreeState& apvts, 
    juce::String attackIdAmp, juce::String decayIdAmp, juce::String sustainIdAmp, juce::String releaseIdAmp, 
    juce::String attackIdFilter, juce::String decayIdFilter, juce::String sustainIdFilter, juce::String releaseIdFilter) :
    ampAdsrComponent("Amplitude ADSR", ColorPalette::miamipink, apvts, attackIdAmp, decayIdAmp, sustainIdAmp, releaseIdAmp), 
    filterAdsrComponent("Filter ADSR", ColorPalette::miamiblue, apvts, attackIdFilter, decayIdFilter, sustainIdFilter, releaseIdFilter)
{
    addAndMakeVisible(ampAdsrComponent);
    addAndMakeVisible(filterAdsrComponent);
}

ADSRView::~ADSRView()
{
}

void ADSRView::paint (juce::Graphics& g)
{
    g.setColour(ColorPalette::monwhite);
    g.setFont(44.0f);

    auto padding = 16;

    auto elementsBounds = getLocalBounds().reduced(padding);
    auto textBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() / 8);
    g.drawFittedText(viewTitle, textBounds, juce::Justification::centred, true);

    elementsBounds.setPosition(juce::Point<int>(elementsBounds.getPosition().getX(), textBounds.getBottom() + padding));
    elementsBounds.setSize(elementsBounds.getWidth(), elementsBounds.getHeight() - textBounds.getHeight() - padding);
}

void ADSRView::resized()
{
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
