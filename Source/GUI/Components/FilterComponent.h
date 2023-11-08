/*
  ==============================================================================

    FilterComponent.h
    FilterComponent class -> Inherits from juce::Component
        - Part of the UI related to the filter
            - Controls and attachments associated with APVTS


  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Assets/ColorPalette.h"
#include "../Assets/CustomControls.h"
#include "../Source/ParamsIDList.h"

//==============================================================================
/*
*/
class FilterComponent : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::Colour borderColour, juce::String filterBypassedId, juce::String filterModeSelectorId, juce::String filterCutoffFreqId, juce::String filterResonanceId);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::String filterTitle = "State Variable Filter";
    juce::Colour filterBorderColour;

    juce::ComboBox filterModeSelector;

    CustomBypassButton filterBypassedButton;

    CustomSliderWithLabel filterCutoffFreqSlider;
    CustomSliderWithLabel filterResonanceSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> filterBypassedButtonAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterModeSelectorAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterCutoffFreqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterResonanceAttachment;

    void setupFilterModeSelector(bool bypassed = false);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
