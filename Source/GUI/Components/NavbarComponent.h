/*
  ==============================================================================

    NavbarComponent.h
    Created: 20 Oct 2022 5:40:57pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class NavbarComponent  : public juce::Component
{
public:
    NavbarComponent();
    ~NavbarComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NavbarComponent)
};
