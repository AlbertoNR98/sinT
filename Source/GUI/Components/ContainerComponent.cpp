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
// Probar a implementar lo anterior haciendo uso del APVTS. De esta forma, pueden utilizarse punteros de Views (que se pueden crear de forma dinámica) y liberar memoria cuando no se vea -> El estado de los sliders se obtendrá del APVTS, por lo que no hará falta guardarlo en otro sitio.
// NOTA: Ver clase SinTContent (basada en clases DemoContent y CodeContent, del proyecto DemoRunner) -> No está implementada del todo pero la idea era más o menos esa.
//==============================================================================
ContainerComponent::ContainerComponent(juce::AudioProcessorValueTreeState& apvts) : m_invokeSidePanel("Sidepanel", "Show Sidepanel")
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    //oscView = new OscView();

    //addChildComponent(homeView);
    addAndMakeVisible(homeView);

    //addChildComponent(oscView);
    //addChildComponent(filterView);

    //addAndMakeVisible(m_invokeSidePanel);
    addAndMakeVisible(m_sidePanelStatus);
    addAndMakeVisible(m_sidePanel);

    m_sidePanelStatus.setText("status", juce::dontSendNotification);
    setSize(600, 400);

    m_invokeSidePanel.addListener(this);

    auto sidePanelList = new SidePanelList;
    sidePanelList->addEntry("OSC");
    sidePanelList->addEntry("FILTER");
    sidePanelList->addEntry("ADSR");
    sidePanelList->addEntry("FX");
    sidePanelList->setEntrySelectionCallback([&](int index) { listEntryClicked(index); });
    m_sidePanel.setContent(sidePanelList);

    auto sidePanelHeader = new SidePanelHeader("Side Panel");
    sidePanelHeader->setHomeButtonClicked([&]() { homeButtonClicked(); });
    sidePanelHeader->setSettingButtonClicked([&]() { settingsButtonClicked(); });
    //m_sidePanel.setTitleBarComponent(sidePanelHeader, true);
    m_sidePanel.setTitleBarComponent(sidePanelHeader, false);
    m_sidePanel.setShadowWidth(0);
}

ContainerComponent::~ContainerComponent()
{
    m_invokeSidePanel.removeListener(this);
}

void ContainerComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    if (m_showingSidePanel)
    {
        comp->setBounds(m_sidePanelWidth, 0, getWidth() - m_sidePanelWidth, getHeight());
    }
    else
    {
        comp->setBounds(0, 0, getWidth(), getHeight());
    }

    //g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colours::cadetblue);
    //g.fillAll(juce::Colours::deeppink);
    //g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::grey);
    //g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(juce::Colours::white);
    g.setFont(14.0f);
    g.drawText("ContainerComponent", getLocalBounds(),
        juce::Justification::centred, true);   // draw some placeholder text
}

void ContainerComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
        //m_sidePanel.setBounds(0, getHeight() / 8, getWidth(), getHeight() - (getHeight() / 8)); -> No funciona
    if (m_showingSidePanel)
    {
        comp->setBounds(m_sidePanelWidth, 0, getWidth() - m_sidePanelWidth, getHeight());
    }
    else
    {
        comp->setBounds(0, 0, getWidth(), getHeight());
    }

    auto localBounds = getLocalBounds();
    if (localBounds.getHeight() / 2 - 50 > 5)
        localBounds.removeFromTop(localBounds.getHeight() / 2 - 50);
    if (localBounds.getWidth() / 2 - 50 > 5)
        localBounds.removeFromLeft(localBounds.getWidth() / 2 - 50);

    auto buttonBound = localBounds.removeFromTop(30).removeFromRight(150);
    auto statusLabelBound = localBounds.removeFromTop(30).removeFromRight(150).reduced(5);
    m_invokeSidePanel.setBounds(buttonBound);
    m_sidePanelStatus.setBounds(statusLabelBound);

    m_sidePanel.setColour(juce::SidePanel::ColourIds::backgroundColour, juce::Colours::orange);
    m_sidePanel.setColour(juce::SidePanel::ColourIds::titleTextColour, juce::Colours::deepskyblue);

    m_sidePanel.showOrHide(true);
}

void ContainerComponent::buttonClicked(juce::Button* btn)
{
    if (btn == &m_invokeSidePanel)
    {
        if (m_showingSidePanel)
        {
            m_sidePanel.showOrHide(false);
        }
        else
        {
            m_sidePanel.showOrHide(true);
        }
        m_showingSidePanel = !m_showingSidePanel;
    }
}

void ContainerComponent::setView(juce::Component& newComponent)
{
    //comp.reset(newComponent);
    //clearCurrentView();
    comp = &newComponent;

    if (comp != nullptr)
    {
        addAndMakeVisible(comp);
        //comp->setVisible(true);
        //comp->setBounds(getLocalBounds());
        //comp->setBounds(250, 0, getWidth() - 250, getHeight());
    }
}

/*
void ContainerComponent::setView(juce::Component& newComponent)
{
    newComponent.setVisible(true);
    newComponent.setBounds(250, 0, getWidth() - 250, getHeight());
}
*/

void ContainerComponent::clearCurrentView()
{
    /*
    sinTContent->setComponent(nullptr);
    demoChangedCallback(false);
    */
    //setView(nullptr);
    comp->setVisible(false);
}

void ContainerComponent::homeButtonClicked()
{
    clearCurrentView();
    setView(homeView);
    m_sidePanelStatus.setText("Home Button clicked", juce::dontSendNotification);
}

void ContainerComponent::settingsButtonClicked()
{
    m_sidePanelStatus.setText("Settings Button clicked", juce::dontSendNotification);
}

void ContainerComponent::listEntryClicked(int index)
{
    //m_sidePanelStatus.setText(juce::String("Entry ") + juce::String(index + 1) + " Clicked", juce::dontSendNotification);

    switch (index)
    {
    case 0:
        //m_sidePanelStatus.setText("OSC clicked", juce::dontSendNotification);
        //clearCurrentView();
        clearCurrentView();
        //setView(oscView);   // Usar punteros -> Viene mejor para poder destruirlos cuando no se usen
        break;
    case 1:
        //oscView->setVisible(false);
        //clearCurrentView();
        clearCurrentView();
        //setView(filterView);
        //m_sidePanelStatus.setText("Filter clicked", juce::dontSendNotification);
        break;
    case 2:
        //m_sidePanelStatus.setText("ADSR clicked", juce::dontSendNotification);
        clearCurrentView();
        break;
    case 3:
        //m_sidePanelStatus.setText("FX clicked", juce::dontSendNotification);
        clearCurrentView();
        break;
    default:
        clearCurrentView();
        setView(homeView);
    }
}
