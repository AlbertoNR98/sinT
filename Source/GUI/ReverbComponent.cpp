/*
  ==============================================================================

    ReverbComponent.cpp
    Metodos de ReverbComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbComponent.h"

//==============================================================================
ReverbComponent::ReverbComponent(juce::AudioProcessorValueTreeState& apvts, juce::String roomSizeId, juce::String widthId, juce::String dampingId, juce::String freezeModeId, juce::String dryLevelId, juce::String wetLevelId)
{
    roomSizeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(roomSizeSlider);

    widthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(widthSlider);

    dampingSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(dampingSlider);

    freezeModeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(freezeModeSlider);

    dryLevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(dryLevelSlider);

    wetLevelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(wetLevelSlider);

    roomSizeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, roomSizeId, roomSizeSlider);
    widthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, widthId, widthSlider);
    dampingAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, dampingId, dampingSlider);
    freezeModeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, freezeModeId, freezeModeSlider);
    dryLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, dryLevelId, dryLevelSlider);
    wetLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, wetLevelId, wetLevelSlider);

}

ReverbComponent::~ReverbComponent()
{
}

void ReverbComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void ReverbComponent::resized()
{
    roomSizeSlider.setBounds(0, 0, 300, 30);
    widthSlider.setBounds(0, roomSizeSlider.getBottom(), 300, 30);
    dampingSlider.setBounds(0, widthSlider.getBottom(), 300, 30);
    freezeModeSlider.setBounds(0, dampingSlider.getBottom(), 300, 30);
    dryLevelSlider.setBounds(0, freezeModeSlider.getBottom(), 300, 30);
    wetLevelSlider.setBounds(0, dryLevelSlider.getBottom(), 300, 30);
}