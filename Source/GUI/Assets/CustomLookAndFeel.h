/*
  ==============================================================================

    CustomLookAndFeel.h
    LookAndFeel classes for sinT

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "ColorPalette.h"

using namespace juce;

class CustomLookAndFeel : public LookAndFeel_V4
{
public:
    CustomLookAndFeel();
    ~CustomLookAndFeel() override;

    virtual void drawButtonText(Graphics& g, TextButton& button,
        [[maybe_unused]] bool shouldDrawButtonAsHighlighted, [[maybe_unused]] bool shouldDrawButtonAsDown) override;

    virtual void drawPopupMenuBackground(Graphics& g, int width, int height) override;

    virtual void drawPopupMenuItem(Graphics& g, const Rectangle<int>& area,
        const bool isSeparator, const bool isActive,
        const bool isHighlighted, const bool isTicked,
        const bool hasSubMenu, const String& text,
        const String& shortcutKeyText,
        [[maybe_unused]] const Drawable* icon, const Colour* const textColourToUse) override;

    virtual void drawLabel(Graphics& g, Label& label) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomLookAndFeel)
};
