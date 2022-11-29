/*
  ==============================================================================

    ContainerComponent.cpp
    Created: 20 Oct 2022 5:41:13pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#include <JuceHeader.h>

#include "ContainerComponent.h"

ContainerComponent::ContainerComponent(juce::AudioProcessorValueTreeState& apvts) :
    valueTree(apvts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    contentComponent.reset(new HomeView());

    addAndMakeVisible(contentComponent.get());
    addAndMakeVisible(sidePanel);

    setSize(600, 400);

    auto sidePanelList = new SidePanelList;
    sidePanelList->addEntry("OSC");
    sidePanelList->addEntry("ADSR");
    sidePanelList->addEntry("FILTER");
    sidePanelList->addEntry("FX");
    sidePanelList->setEntrySelectionCallback([&](int index) { listEntryClicked(index); });
    sidePanel.setContent(sidePanelList);

    auto sidePanelHeader = new SidePanelHeader("Side Panel");
    sidePanelHeader->setHomeButtonClicked([&]() { homeButtonClicked(); });
    sidePanelHeader->setSettingButtonClicked([&]() { settingsButtonClicked(); });
    //sidePanel.setTitleBarComponent(sidePanelHeader, true);
    sidePanel.setTitleBarComponent(sidePanelHeader, false);
    sidePanel.setShadowWidth(0);
}

ContainerComponent::~ContainerComponent()
{
}

void ContainerComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    if (showingSidePanel)
    {
        contentComponent->setBounds(sidePanelWidth, 0, getWidth() - sidePanelWidth, getHeight());
    }
    else
    {
        contentComponent->setBounds(0, 0, getWidth(), getHeight());
    }

    //g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    //g.fillAll(juce::Colours::cadetblue);
    g.fillAll(juce::Colours::black);

    g.setColour(juce::Colours::white);
    g.setFont(14.0f);
    g.drawText("ContainerComponent", getLocalBounds(),
        juce::Justification::centred, true);   // draw some placeholder text
}

void ContainerComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    if (showingSidePanel)
    {
        sidePanel.showOrHide(true);
        contentComponent->setBounds(sidePanelWidth, 0, getWidth() - sidePanelWidth, getHeight());
    }
    else
    {
        sidePanel.showOrHide(false);
        contentComponent->setBounds(0, 0, getWidth(), getHeight());
    }

    auto localBounds = getLocalBounds();
    if (localBounds.getHeight() / 2 - 50 > 5)
        localBounds.removeFromTop(localBounds.getHeight() / 2 - 50);
    if (localBounds.getWidth() / 2 - 50 > 5)
        localBounds.removeFromLeft(localBounds.getWidth() / 2 - 50);

    //auto statusLabelBound = localBounds.removeFromTop(30).removeFromRight(150).reduced(5);
    //sidePanelStatus.setBounds(statusLabelBound);

    sidePanel.setColour(juce::SidePanel::ColourIds::backgroundColour, juce::Colours::orange);
    sidePanel.setColour(juce::SidePanel::ColourIds::titleTextColour, juce::Colours::deepskyblue);
}

void ContainerComponent::setView(const int selectedView)
{
    using namespace ParamsIDList;

    switch (selectedView)
    {
        case OSC_VIEW:
            contentComponent.reset(new OscView(valueTree, osc1Bypassed, osc1Waveform, osc1Gain, osc1Pitch, osc1FmFreq, osc1FmDepth, osc2Bypassed, osc2Waveform, osc2Gain, osc2Pitch, osc2FmFreq, osc2FmDepth));
            break;
        case ADSR_VIEW:
            contentComponent.reset(new ADSRView(valueTree, ampAdsrAttack, ampAdsrDecay, ampAdsrSustain, ampAdsrRelease, filterAdsrAttack, filterAdsrDecay, filterAdsrSustain, filterAdsrRelease));
            break;
        case FILTER_VIEW:
            contentComponent.reset(new FilterView(valueTree, filterBypassed, filterMode, filterCutoffFreq, filterResonance, lfoFreq, lfoDepth));
            break;
        case FX_VIEW:
            break;
        case HOME_VIEW:
            contentComponent.reset(new HomeView());
            break;
        default:
            contentComponent.reset(new HomeView());
    }

    addAndMakeVisible(contentComponent.get());
}

void ContainerComponent::homeButtonClicked()
{
    if (contentComponent != nullptr)
        setView(HOME_VIEW);
}

void ContainerComponent::settingsButtonClicked()
{
    if (contentComponent != nullptr)
        setView(HOME_VIEW);
}

void ContainerComponent::listEntryClicked(int index)
{
    switch (index)
    {
        case OSC_VIEW:
            setView(OSC_VIEW);
            break;
        case ADSR_VIEW:
            setView(ADSR_VIEW);
            break;
        case FILTER_VIEW:
            setView(FILTER_VIEW);
            break;
        case FX_VIEW:
            setView(FX_VIEW);
            break;
        default:
            setView(HOME_VIEW);
    }
}
