/*
  ==============================================================================

    MainComponent.h
    Created: 20 Oct 2022 5:51:21pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../PluginProcessor.h"

#include "ContainerComponent.h"
#include "NavbarComponent.h"

//==============================================================================
/*
*/
class MainComponent  : public juce::Component
{
public:
    //MainComponent(juce::AudioProcessorValueTreeState& apvts);
    MainComponent(SinTAudioProcessor& audioProcessor);
    ~MainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    NavbarComponent navbarComponent;
    ContainerComponent containerComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
