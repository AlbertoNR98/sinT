/*
  ==============================================================================

    OscillatorComponent.cpp
    Metodos de OscillatorComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscillatorComponent.h"

//==============================================================================
OscillatorComponent::OscillatorComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String waveformSelectorId, juce::String oscGainId, juce::String oscPitchId, juce::String fmFreqId, juce::String fmDepthId)
{
/*
oscName.setText(name, juce::dontSendNotification);
oscName.setEditable(false);
addAndMakeVisible(oscName);
*/
    oscName = name;

    juce::StringArray waveOptions{ "Sine", "Saw", "Square" };
    oscWaveSelector.addItemList(waveOptions, 1);
    addAndMakeVisible(oscWaveSelector);

    oscGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(oscGainSlider);

    oscPitchSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(oscPitchSlider);

    fmFreqSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(fmFreqSlider);

    fmDepthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(fmDepthSlider);

    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveformSelectorId, oscWaveSelector);
    oscGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, oscGainId, oscGainSlider);
    oscPitchAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, oscPitchId, oscPitchSlider);
    fmFreqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, fmFreqId, fmFreqSlider);
    fmDepthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, fmDepthId, fmDepthSlider);
}

OscillatorComponent::~OscillatorComponent()
{
}

void OscillatorComponent::paint (juce::Graphics& g)
{
    //g.fillAll(juce::Colours::black);
    g.fillAll(juce::Colours::cadetblue);

    //g.setColour(juce::Colours::white);
    g.setColour(juce::Colours::wheat);
    
    auto localBounds = getLocalBounds();
    //g.drawRoundedRectangle(localBounds.getPosition().getX(), localBounds.getPosition().getY(), localBounds.getWidth(), localBounds.getHeight(), 10.0f, 10.0f);
    g.drawRect(localBounds, 5.f);

    auto textBounds = juce::Rectangle<int>(localBounds.getWidth(), localBounds.getHeight() / 6);
    textBounds.setPosition(localBounds.getPosition());
    g.setFont(24.f);
    g.drawFittedText(oscName, textBounds, juce::Justification::centred, true);

}

void OscillatorComponent::resized()
{
    auto elementsBounds = getLocalBounds().reduced(25);

    //oscName.setBounds -> Se puede hacer si es label en lugar de string
    //oscWaveSelector.setBounds(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY(), elementsBounds.getWidth() / 2, elementsBounds.getHeight() / 6);
    oscWaveSelector.setBounds(elementsBounds.getPosition().getX(), elementsBounds.getPosition().getY() + (elementsBounds.getHeight() / 6), elementsBounds.getWidth() / 2, elementsBounds.getHeight() / 6);
    oscGainSlider.setBounds(elementsBounds.getPosition().getX(), oscWaveSelector.getBottom(), elementsBounds.getWidth(), elementsBounds.getHeight() / 6);
    oscPitchSlider.setBounds(elementsBounds.getPosition().getX(), oscGainSlider.getBottom(), elementsBounds.getWidth(), elementsBounds.getHeight() / 6);
    fmFreqSlider.setBounds(elementsBounds.getPosition().getX(), oscPitchSlider.getBottom(), elementsBounds.getWidth(), elementsBounds.getHeight() / 6);
    fmDepthSlider.setBounds(elementsBounds.getPosition().getX(), fmFreqSlider.getBottom(), elementsBounds.getWidth(), elementsBounds.getHeight() / 6);
}
