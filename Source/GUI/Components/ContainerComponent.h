/*
  ==============================================================================

    ContainerComponent.h
    Created: 20 Oct 2022 5:41:13pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ContainerComponent  : public juce::Component
{
public:
    ContainerComponent();
    ~ContainerComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ContainerComponent)
};
