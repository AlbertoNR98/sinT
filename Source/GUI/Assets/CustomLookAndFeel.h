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

class CustomLookAndFeel  : public LookAndFeel_V4
{
public:
    CustomLookAndFeel();
    ~CustomLookAndFeel() override;

    virtual void drawButtonText(Graphics& g, TextButton& button, [[maybe_unused]] bool shouldDrawButtonAsHighlighted, [[maybe_unused]] bool shouldDrawButtonAsDown) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomLookAndFeel)
};
