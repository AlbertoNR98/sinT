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
    scopeComponent(audioProcessor.getAudioBufferQueue())
{
    addAndMakeVisible(scopeComponent);
}

ScopeView::~ScopeView()
{
}

void ScopeView::paint (juce::Graphics& g)
{
    g.setColour(ColorPalette::monwhite);
    g.setFont(44.0f);

    auto boundsPadding = 16;

    auto elementsBounds = getLocalBounds().reduced(boundsPadding);
    auto textBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() / 8);
    g.drawFittedText(viewTitle, textBounds, juce::Justification::centred, true);

    g.setColour(ColorPalette::miamiblue);
    elementsBounds.setPosition(juce::Point<int>(elementsBounds.getPosition().getX(), textBounds.getBottom() + boundsPadding));
    elementsBounds.setSize(elementsBounds.getWidth(), elementsBounds.getHeight() - textBounds.getHeight() - boundsPadding);
    g.drawRoundedRectangle(elementsBounds.toFloat(), 10.0f, 2.0f);
}

void ScopeView::resized()
{
    auto padding = 16;

    auto elementsBounds = getLocalBounds().reduced(padding);

    auto textBounds = juce::Rectangle<int>(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth(), elementsBounds.getHeight() / 8);

    elementsBounds.setPosition(juce::Point<int>(elementsBounds.getPosition().getX(), textBounds.getBottom() + padding));
    elementsBounds.setSize(elementsBounds.getWidth(), elementsBounds.getHeight() - textBounds.getHeight() - padding);

    scopeComponent.setBounds(elementsBounds);
}
