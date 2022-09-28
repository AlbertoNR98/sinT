/*
  ==============================================================================

    ADSRComponent.cpp
    Metodos de ADSRComponent

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRComponent.h"

//==============================================================================
ADSRComponent::ADSRComponent(juce::AudioProcessorValueTreeState& apvts, juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId)
{
    //Attachments
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    attackAttachment = std::make_unique<SliderAttachment>(apvts, attackId, attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(apvts, decayId, decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, sustainId, sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, releaseId, releaseSlider);

    // Estilo de sliders ADSR
    setSliderVisualParams(attackSlider);
    setSliderVisualParams(decaySlider);
    setSliderVisualParams(sustainSlider);
    setSliderVisualParams(releaseSlider);
}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void ADSRComponent::resized()
{
    // Posicionamiento de los sliders ADSR en la GUI
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;

    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight();
    const auto sliderStartX = 0;
    const auto sliderStartY = 0;

    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

}

void ADSRComponent::setSliderVisualParams(juce::Slider& slider)
{
    // Estilo de slider para ADSR
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);

    addAndMakeVisible(slider);
}
