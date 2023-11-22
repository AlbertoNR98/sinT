/*
  ==============================================================================

    ScopeView.cpp
    Metodos de ScopeView

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ScopeView.h"

//==============================================================================
ScopeView::ScopeView(SinTAudioProcessor& audioProcessor) :
    leftScopeComponent("Left", audioProcessor.getAudioBufferQueue(0)),
    rightScopeComponent("Right", audioProcessor.getAudioBufferQueue(1))
{
    addAndMakeVisible(leftScopeComponent);
    addAndMakeVisible(rightScopeComponent);
}

ScopeView::~ScopeView()
{
}

void ScopeView::paint (juce::Graphics& g)
{
    g.setColour(ColorPalette::monwhite);

    auto boundsPadding = 16;

    auto elementsBounds = getLocalBounds().reduced(boundsPadding);
    auto textBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() / 8);
    drawTitle(g, viewTitle, textBounds, juce::Justification::centred, 44.0f, 0.75f);

    g.setColour(ColorPalette::miamiblue);
    elementsBounds.setPosition(juce::Point<int>(elementsBounds.getPosition().getX(), textBounds.getBottom() + boundsPadding));
    elementsBounds.setSize(elementsBounds.getWidth(), elementsBounds.getHeight() - textBounds.getHeight() - boundsPadding);
    g.drawRoundedRectangle(elementsBounds.toFloat(), 6.0f, 3.5f);
}

void ScopeView::resized()
{
    auto padding = 16;

    auto elementsBounds = getLocalBounds().reduced(padding);

    auto textBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() / 8);

    elementsBounds.setPosition(juce::Point<int>(elementsBounds.getPosition().getX(), textBounds.getBottom() + padding));
    elementsBounds.setSize(elementsBounds.getWidth(), (elementsBounds.getHeight() - textBounds.getHeight() - padding));


    auto leftScopeBounds = elementsBounds;
    leftScopeBounds.setSize(elementsBounds.getWidth(), (elementsBounds.getHeight() / 2 ) - padding / 2);
    leftScopeComponent.setBounds(leftScopeBounds);

    auto rightScopeBounds = elementsBounds;
    rightScopeBounds.setTop(leftScopeBounds.getBottom() + padding);
    rightScopeComponent.setBounds(rightScopeBounds);
}
