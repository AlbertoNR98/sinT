/*
  ==============================================================================

    NavbarComponent.cpp
    Metodos de NavbarComponent

  ==============================================================================
*/

#include "NavbarComponent.h"

//==============================================================================
NavbarComponent::NavbarComponent(SinTAudioProcessor& audioProcessor, ContainerComponent& c) : 
    containerComponent(c), 
    showSidePanelButton("-", "Show Sidepanel"), 
    gainMeter([&]()->std::pair<float, float> { return audioProcessor.getMainGainMeterRmsValues(); }),
    mainControl(audioProcessor.apvts, ParamsIDList::mainGain, ParamsIDList::portamento),
    presetManager(audioProcessor.getPresetManager())
{
    showSidePanelButton.setColour(juce::TextButton::buttonColourId, ColorPalette::orthzul);
    showSidePanelButton.setColour(juce::ComboBox::outlineColourId, ColorPalette::monwhite);
    addAndMakeVisible(showSidePanelButton);

    addAndMakeVisible(gainMeter);
    addAndMakeVisible(mainControl);
    addAndMakeVisible(presetManager);

    showSidePanelButton.addListener(this);
}

NavbarComponent::~NavbarComponent()
{
    showSidePanelButton.removeListener(this);
}

void NavbarComponent::paint (juce::Graphics& g)
{
    g.fillAll(ColorPalette::orthzul);
}

void NavbarComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(7);
    const auto padding = bounds.getWidth() * 0.01;

    const auto showSidePanelButtonBounds = juce::Rectangle<int>(bounds.getTopLeft().getX(), bounds.getTopLeft().getY(), bounds.getWidth() * 0.07, bounds.getHeight());
    const auto mainControlBounds = juce::Rectangle<int>(showSidePanelButtonBounds.getRight() + padding, bounds.getTopLeft().getY(), bounds.getWidth() * 0.3, bounds.getHeight());
    const auto presetManagerBounds = juce::Rectangle<int>(mainControlBounds.getRight() + padding, bounds.getTopLeft().getY(), bounds.getWidth() * 0.45, bounds.getHeight());
    const auto gainMeterBounds = juce::Rectangle<int>(presetManagerBounds.getRight() + padding, bounds.getTopLeft().getY(), bounds.getWidth() * 0.15, bounds.getHeight());

    showSidePanelButton.setBounds(showSidePanelButtonBounds);
    mainControl.setBounds(mainControlBounds);
    presetManager.setBounds(presetManagerBounds);
    gainMeter.setBounds(gainMeterBounds);
}

void NavbarComponent::buttonClicked(juce::Button* btn)
{
    if (btn == &showSidePanelButton)
    {
        if (containerComponent.isShowingSidePanel())
        {
            showSidePanelButton.setButtonText("+");
            containerComponent.getSidePanel().showOrHide(false);
        }
        else
        {
            showSidePanelButton.setButtonText("-");
            containerComponent.getSidePanel().showOrHide(true);
        }
        containerComponent.setShowingSidePanel(!containerComponent.isShowingSidePanel());
    }
}
