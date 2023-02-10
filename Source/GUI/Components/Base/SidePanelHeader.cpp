/*
  ==============================================================================

    SidePanelHeader.cpp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SidePanelHeader.h"

//==============================================================================
SidePanelHeader::SidePanelHeader(const juce::String& titleText) : titleAboutButton("")
{
    setOpaque(true);

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

    titleAboutButton.setColour(juce::TextButton::buttonColourId, ColorPalette::transparentwhite);
    titleAboutButton.setColour(juce::TextButton::textColourOnId, ColorPalette::miamiblue);
    titleAboutButton.setColour(juce::TextButton::textColourOffId, ColorPalette::miamiblue);
    titleAboutButton.setColour(juce::ComboBox::outlineColourId, ColorPalette::transparentwhite);

#if JUCE_LINUX && JUCE_STANDALONE_FILTER_WINDOW_USE_KIOSK_MODE
    addAndMakeVisible(settingsButton);
#endif
    addAndMakeVisible(titleAboutButton);
}

SidePanelHeader::~SidePanelHeader()
{
}

void SidePanelHeader::paint (juce::Graphics& g)
{
    g.fillAll(ColorPalette::monwhite);

    auto bounds = getLocalBounds();
    bounds.removeFromLeft(10);
#if JUCE_LINUX && JUCE_STANDALONE_FILTER_WINDOW_USE_KIOSK_MODE
    bounds.removeFromLeft(settingsButton.getWidth() + 20).reduced(7);
    bounds.removeFromLeft(10);
#endif
    bounds.removeFromRight(10);

    g.setFont(28.f);
    g.setColour(ColorPalette::miamiblue);
    g.drawText("sinT", bounds, juce::Justification::centred, 1);

    auto normal = getLookAndFeel().findColour(juce::SidePanel::dismissButtonNormalColour);
    auto over = getLookAndFeel().findColour(juce::SidePanel::dismissButtonOverColour);
    auto down = getLookAndFeel().findColour(juce::SidePanel::dismissButtonDownColour);

    settingsButton.setColours(normal, over, down);
}

void SidePanelHeader::resized()
{
    auto bounds = getLocalBounds();
    bounds.removeFromLeft(10);
#if JUCE_LINUX && JUCE_STANDALONE_FILTER_WINDOW_USE_KIOSK_MODE
    settingsButton.setBounds(bounds.removeFromLeft(settingsButton.getWidth() + 20).reduced(7));
    bounds.removeFromLeft(10);
#endif
    bounds.removeFromRight(10);
    titleAboutButton.setBounds(bounds);

    // TO-DO: Ajustar bordes de titleAboutButton en caso de que no se muestre el boton de settings -> Directivas o .isVisible()
}

void SidePanelHeader::setAboutButtonClicked(std::function<void()> callback)
{
    titleAboutButton.onClick = callback;
}

void SidePanelHeader::setSettingButtonClicked(std::function<void()> callback)
{
    settingsButton.onClick = callback;
}
