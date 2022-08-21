/*
  ==============================================================================

    GainComponent.cpp
    Metodos de GainComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GainComponent.h"

//==============================================================================
GainComponent::GainComponent(juce::AudioProcessorValueTreeState& apvts, juce::String mainGainId)
{
    mainGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(mainGainSlider);

    mainGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, mainGainId, mainGainSlider);
}

GainComponent::~GainComponent()
{
}

void GainComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void GainComponent::resized()
{
    mainGainSlider.setBounds(0, 0, 300, 30);
}
