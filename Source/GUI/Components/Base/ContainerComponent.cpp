/*
  ==============================================================================

    ContainerComponent.cpp
    Created: 20 Oct 2022 5:41:13pm
    Author:  Alberto Naranjo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ContainerComponent.h"

// Actualmente, se usan variables para las View, ya que se requiere que no se reseteen los valores de los sliders una vez dejan de verse.
// Probar a implementar lo anterior haciendo uso del APVTS. De esta forma, pueden utilizarse punteros de Views (que se pueden crear de forma din�mica) y liberar memoria cuando no se vea -> El estado de los sliders se obtendr� del APVTS, por lo que no har� falta guardarlo en otro sitio.
// NOTA: Ver clase SinTContent -> No esta implementada del todo pero la idea era mas o menos esa.
//==============================================================================

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
    sidePanelList->addEntry("FILTER");
    sidePanelList->addEntry("ADSR");
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
    switch (selectedView)
    {
        case OSC_VIEW:
            contentComponent.reset(new OscView(valueTree, "OSC1BYPASSED", "OSC1WF", "OSC1GAINDB", "OSC1PITCH", "OSC1FMFREQ", "OSC1FMDEPTH", "OSC2BYPASSED", "OSC2WF", "OSC2GAINDB", "OSC2PITCH", "OSC2FMFREQ", "OSC2FMDEPTH"));
            break;
        case FILTER_VIEW:
            break;
        case ADSR_VIEW:
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
        case FILTER_VIEW:
            setView(FILTER_VIEW);
            break;
        case ADSR_VIEW:
            setView(ADSR_VIEW);
            break;
        case FX_VIEW:
            setView(FX_VIEW);
            break;
        default:
            setView(HOME_VIEW);
    }
}