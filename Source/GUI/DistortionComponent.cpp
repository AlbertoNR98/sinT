/*
  ==============================================================================

    DistortionComponent.cpp
    Metodos de DistortionComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DistortionComponent.h"

//==============================================================================
DistortionComponent::DistortionComponent(juce::AudioProcessorValueTreeState& apvts, juce::String driveId, juce::String rangeId, juce::String blendId, juce::String volumeId)
{
    driveSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(driveSlider);

    rangeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(rangeSlider);

    blendSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(blendSlider);

    volumeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(volumeSlider);

    driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, driveId, driveSlider);
    rangeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, rangeId, rangeSlider);
    blendAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, blendId, blendSlider);
    volumeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, volumeId, volumeSlider);
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
    volumeSlider.setBounds(0, blendSlider.getBottom(), 300, 30);
}
