/*
  ==============================================================================

    HomeView.cpp
    Created: 20 Oct 2022 5:39:57pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "HomeView.h"

//==============================================================================
HomeView::HomeView()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

HomeView::~HomeView()
{
}

void HomeView::paint (juce::Graphics& g)
{
    g.setColour (ColorPalette::monwhite);
    g.setFont (180.0f);
    g.drawText ("sinT", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void HomeView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
