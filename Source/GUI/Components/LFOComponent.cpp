/*
  ==============================================================================

    LFOComponent.cpp
    Metodos de LFOComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LFOComponent.h"

//==============================================================================
LFOComponent::LFOComponent(juce::AudioProcessorValueTreeState& apvts, juce::String lfoFreqId, juce::String lfoDepthId)
{
    lfoFreqSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(lfoFreqSlider);

    lfoDepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(lfoDepthSlider);

    lfoFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, lfoFreqId, lfoFreqSlider);
    lfoDepthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, lfoDepthId, lfoDepthSlider);
}

LFOComponent::~LFOComponent()
{
}

void LFOComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void LFOComponent::resized()
{
    lfoFreqSlider.setBounds(0, 0, 300, 30);
    lfoDepthSlider.setBounds(0, lfoFreqSlider.getBottom(), 300, 30);
}
