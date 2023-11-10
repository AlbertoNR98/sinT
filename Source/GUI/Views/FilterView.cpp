/*
  ==============================================================================

    FilterView.cpp
    Metodos de FilterView

  ==============================================================================
*/

#include "FilterView.h"

//==============================================================================
FilterView::FilterView(juce::AudioProcessorValueTreeState& apvts, 
    juce::String filterBypassedId, juce::String filterModeSelectorId, juce::String filterCutoffFreqId, juce::String filterResonanceId, 
    juce::String lfoFreqId, juce::String lfoDepthId) :
    filterComponent(apvts, ColorPalette::orthzul, filterBypassedId, filterModeSelectorId, filterCutoffFreqId, filterResonanceId),
    lfoComponent(apvts, ColorPalette::miamipink, lfoFreqId, lfoDepthId)
{
    addAndMakeVisible(filterComponent);
    addAndMakeVisible(lfoComponent);
}

FilterView::~FilterView()
{
}

void FilterView::paint (juce::Graphics& g)
{
    g.setColour(ColorPalette::monwhite);

    auto padding = 16;

    auto elementsBounds = getLocalBounds().reduced(padding);
    auto textBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() / 8);
    drawTitle(g, viewTitle, textBounds, juce::Justification::centred, 44.0f, 0.75f);

    elementsBounds.setPosition(juce::Point<int>(elementsBounds.getPosition().getX(), textBounds.getBottom() + padding));
    elementsBounds.setSize(elementsBounds.getWidth(), elementsBounds.getHeight() - textBounds.getHeight() - padding);
}

void FilterView::resized()
{
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
