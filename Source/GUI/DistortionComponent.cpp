/*
  ==============================================================================

    DistortionComponent.cpp
    Metodos de DistortionComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DistortionComponent.h"

//==============================================================================
DistortionComponent::DistortionComponent(juce::AudioProcessorValueTreeState& apvts, juce::String driveId, juce::String rangeId, juce::String blendId)
{
    driveSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(driveSlider);

    rangeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(rangeSlider);

    blendSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(blendSlider);

    driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, driveId, driveSlider);
    rangeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, rangeId, rangeSlider);
    blendAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, blendId, blendSlider);
}

DistortionComponent::~DistortionComponent()
{
}

void DistortionComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void DistortionComponent::resized()
{
    driveSlider.setBounds(0, 0, 300, 30);
    rangeSlider.setBounds(0, driveSlider.getBottom(), 300, 30);
    blendSlider.setBounds(0, rangeSlider.getBottom(), 300, 30);
}
