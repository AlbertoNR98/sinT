/*
  ==============================================================================

    NavbarComponent.cpp
    Created: 20 Oct 2022 5:40:57pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "NavbarComponent.h"

//==============================================================================
NavbarComponent::NavbarComponent(SinTAudioProcessor& audioProcessor, ContainerComponent& c) : 
    containerComponent(c), 
    showSidePanel("Sidepanel", "Show Sidepanel"), 
    settingsButton("Settings", juce::Colours::transparentBlack, juce::Colours::transparentBlack, juce::Colours::transparentBlack),
    gainMeter([&]()->std::pair<float, float> { return audioProcessor.getMainGainMeterRmsValues(); }),
    mainControl(audioProcessor.apvts, "MAINGAIN", "PORTAMENTO")
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    static const unsigned char settingsIconPathData[]
        = { 110,109,202,111,210,64,243,226,61,64,108,0,0,224,64,0,0,0,0,108,0,0,48,65,0,0,0,0,108,27,200,54,65,243,
            226,61,64,98,91,248,63,65,174,170,76,64,95,130,72,65,231,138,96,64,46,46,80,65,180,163,120,64,108,42,
            181,124,65,20,38,49,64,108,149,90,142,65,246,108,199,64,108,68,249,118,65,2,85,1,65,98,112,166,119,65,
            201,31,6,65,0,0,120,65,111,5,11,65,0,0,120,65,0,0,16,65,98,0,0,120,65,145,250,20,65,108,166,119,65,55,
            224,25,65,72,249,118,65,254,170,30,65,108,151,90,142,65,133,73,60,65,108,46,181,124,65,123,182,115,65,
            108,50,46,80,65,18,215,97,65,98,99,130,72,65,70,221,103,65,96,248,63,65,83,213,108,65,32,200,54,65,66,
            135,112,65,108,0,0,48,65,0,0,144,65,108,0,0,224,64,0,0,144,65,108,202,111,210,64,67,135,112,65,98,74,
            15,192,64,84,213,108,65,65,251,174,64,70,221,103,65,164,163,159,64,19,215,97,65,108,92,43,13,64,123,182,
            115,65,108,187,181,82,62,133,73,60,65,108,244,26,36,64,254,170,30,65,98,64,102,33,64,55,224,25,5,0,0,32,
            64,145,250,20,65,0,0,32,64,0,0,16,65,98,0,0,32,64,111,5,11,65,64,102,33,64,201,31,6,65,244,26,36,64,2,85,
            1,65,108,187,181,82,62,246,108,199,64,108,92,43,13,64,20,38,49,64,108,164,163,159,64,180,163,120,64,98,65,
            251,174,64,231,138,96,64,74,15,192,64,175,170,76,64,202,111,210,64,243,226,61,64,99,109,0,0,16,65,0,0,64,
            65,98,121,130,42,65,0,0,64,65,0,0,64,65,121,130,42,65,0,0,64,65,0,0,16,65,98,0,0,64,65,13,251,234,64,121,
            130,42,65,0,0,192,64,0,0,16,65,0,0,192,64,98,13,251,234,64,0,0,192,64,0,0,192,64,13,251,234,64,0,0,192,64,
            0,0,16,65,98,0,0,192,64,121,130,42,65,13,251,234,64,0,0,64,65,0,0,16,65,0,0,64,65,99,101,0,0 };

    juce::Path p;
    p.loadPathFromData(settingsIconPathData, sizeof(settingsIconPathData));
    settingsButton.setShape(p, true, true, false);

    addAndMakeVisible(showSidePanel);
    addAndMakeVisible(settingsButton);
    addAndMakeVisible(gainMeter);
    addAndMakeVisible(mainControl);

    showSidePanel.addListener(this);
    settingsButton.addListener(this);
}

NavbarComponent::~NavbarComponent()
{
    showSidePanel.removeListener(this);
    settingsButton.removeListener(this);
}

void NavbarComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.fillAll(juce::Colours::blueviolet);   // clear the background

    g.setColour(juce::Colours::white);
    g.drawRect(getLocalBounds(), 0);   // draw an outline around the component

    g.setFont(14.0f);
    g.drawText("NavbarComponent", getLocalBounds(),
        juce::Justification::centred, true);   // draw some placeholder text

    auto normal = getLookAndFeel().findColour(juce::SidePanel::dismissButtonNormalColour);
    auto over = getLookAndFeel().findColour(juce::SidePanel::dismissButtonOverColour);
    auto down = getLookAndFeel().findColour(juce::SidePanel::dismissButtonDownColour);

    settingsButton.setColours(normal, over, down);
}

void NavbarComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto sidePanelButtonBound = getLocalBounds().removeFromTop(30).removeFromLeft(150);
    auto settingsButtonBound = getLocalBounds().removeFromTop(30).removeFromRight(150);
    auto gainMeterBound = 0;    // TO-DO
    showSidePanel.setBounds(sidePanelButtonBound);
    settingsButton.setBounds(settingsButtonBound);
    //gainMeter.setBounds(300, 0, getWidth() / 4, getHeight());  //TO-DO -> Corregir MeterComponent para que se adapte bien al Navbar
    mainControl.setBounds(300, 0, getWidth() / 4, getHeight());
}

void NavbarComponent::buttonClicked(juce::Button* btn)
{
    if (btn == &showSidePanel)
    {
        if (containerComponent.isShowingSidePanel())
        {
            containerComponent.getSidePanel().showOrHide(false);
        }
        else
        {
            containerComponent.getSidePanel().showOrHide(true);
        }
        containerComponent.setShowingSidePanel(!containerComponent.isShowingSidePanel());
    }

    if (btn == &settingsButton)
    {
        containerComponent.clearCurrentView();
        containerComponent.setView(containerComponent.getHomeView());   // Sustituir por SettingsView
    }
}

