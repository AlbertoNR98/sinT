/*
  ==============================================================================

    ContainerComponent.cpp
    Metodos de ContainerComponent

  ==============================================================================
*/

#include "ContainerComponent.h"

ContainerComponent::ContainerComponent(SinTAudioProcessor& audioProcessor) :
    audioProcessor(audioProcessor)
{
    contentComponent.reset(new HomeView());

    sidePanelList->addEntry("OSC");
    sidePanelList->addEntry("ADSR");
    sidePanelList->addEntry("FILTER");
    sidePanelList->addEntry("FX");
    sidePanelList->addEntry("SCOPE");
    sidePanelList->setEntrySelectionCallback([&](int index) { listEntryClicked(index); });
    sidePanel.setContent(sidePanelList);

    sidePanelHeader->setAboutButtonClicked([&]() { aboutButtonClicked(); });
    sidePanelHeader->setSettingButtonClicked([&]() { settingsButtonClicked(); });
    sidePanel.setTitleBarComponent(sidePanelHeader, false);
    sidePanel.setShadowWidth(0);

    addAndMakeVisible(contentComponent.get());
    addAndMakeVisible(sidePanel);
}

ContainerComponent::~ContainerComponent()
{
}

void ContainerComponent::paint (juce::Graphics& g)
{
    if (showingSidePanel)
    {
        contentComponent->setBounds(sidePanelWidth, 0, getWidth() - sidePanelWidth, getHeight());
    }
    else
    {
        contentComponent->setBounds(0, 0, getWidth(), getHeight());
    }

    g.fillAll(ColorPalette::darkgray);
}

void ContainerComponent::resized()
{
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
}

void ContainerComponent::setView(const int selectedView)
{
    using namespace ParamsIDList;

    switch (selectedView)
    {
        case OSC_VIEW:
            contentComponent.reset(new OscView(audioProcessor.apvts, osc1Bypassed, osc1Waveform, osc1Gain, osc1Pitch, osc1FmFreq, osc1FmDepth,
                                    osc2Bypassed, osc2Waveform, osc2Gain, osc2Pitch, osc2FmFreq, osc2FmDepth));
            break;
        case ADSR_VIEW:
            contentComponent.reset(new ADSRView(audioProcessor.apvts, ampAdsrAttack, ampAdsrDecay, ampAdsrSustain, ampAdsrRelease,
                                    filterAdsrAttack, filterAdsrDecay, filterAdsrSustain, filterAdsrRelease));
            break;
        case FILTER_VIEW:
            contentComponent.reset(new FilterView(audioProcessor.apvts, filterBypassed, filterMode, filterCutoffFreq, filterResonance, lfoFreq, lfoDepth));
            break;
        case FX_VIEW:
            contentComponent.reset(new FXProcessorView(audioProcessor.apvts, distortionBypassed, distortionDrive, distortionRange, distortionBlend,
                                    chorusBypassed, chorusRate, chorusDepth, chorusCentreDelay, chorusFeedback, chorusMix,
                                    delayBypassed, delayTimeMs, delayFeedback,
                                    reverbBypassed, reverbRoomSize, reverbWidth, reverbDamping, reverbFreezeMode, reverbDryLevel, reverbWetLevel));
            break;
        case HOME_VIEW:
            contentComponent.reset(new HomeView());
            break;
        case SCOPE_VIEW:
            contentComponent.reset(new ScopeView(audioProcessor));
            break;
        case SETTINGS_VIEW:
            contentComponent.reset(new SettingsView());
            break;
        default:
            contentComponent.reset(new HomeView());
    }

    addAndMakeVisible(contentComponent.get());
}

void ContainerComponent::aboutButtonClicked()
{
    if (contentComponent != nullptr)
    {
        sidePanelList->getEntries().deselectAllRows();
        setView(HOME_VIEW);
    }
}

void ContainerComponent::settingsButtonClicked()
{
    if (contentComponent != nullptr)
    {
        sidePanelList->getEntries().deselectAllRows();
        setView(SETTINGS_VIEW);
    }
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
        case SCOPE_VIEW:
            setView(SCOPE_VIEW);
            break;
        default:
            setView(HOME_VIEW);
    }
}
