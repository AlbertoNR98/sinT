/*
  ==============================================================================

    CustomLookAndFeel.cpp

  ==============================================================================
*/

#include <JuceHeader.h>

#include "CustomLookAndFeel.h"

//==============================================================================
CustomLookAndFeel::CustomLookAndFeel()
{	
	// Colour IDs customization
	setColour(PopupMenu::backgroundColourId, ColorPalette::basegray);
	setColour(PopupMenu::highlightedBackgroundColourId, ColorPalette::orthzul);
	setColour(PopupMenu::highlightedTextColourId, ColorPalette::monwhite);
}

CustomLookAndFeel::~CustomLookAndFeel()
{
}

void CustomLookAndFeel::drawButtonText(Graphics& g, TextButton& button,
	[[maybe_unused]] bool shouldDrawButtonAsHighlighted, [[maybe_unused]] bool shouldDrawButtonAsDown)
{
	const int yIndent = button.proportionOfHeight(0.1f);
	const int cornerSize = jmin(button.getHeight(), button.getWidth()) / 2;

	const int leftIndent = cornerSize / (button.isConnectedOnLeft() ? yIndent * 2 : yIndent);
	const int rightIndent = cornerSize / (button.isConnectedOnRight() ? yIndent * 2 : yIndent);
	const int textWidth = button.getWidth() - leftIndent - rightIndent;

	int fontSize = button.getHeight() * 0.6;
	Font font(fontSize);

	const int stringLength = font.getStringWidth(button.getButtonText());

	if (stringLength > textWidth)	// Reduces font height if the string doesn't fit on the button
	{
		float scaleFactor = static_cast<float>(textWidth) / static_cast<float>(stringLength);
		font.setHeight(font.getHeight() * scaleFactor);
	}

	g.setFont(font);
	g.setColour(button.findColour(button.getToggleState() ? TextButton::textColourOnId
		: TextButton::textColourOffId)
		.withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f));

	if (textWidth > 0)
	{
		g.drawFittedText(button.getButtonText(), leftIndent, yIndent, textWidth, 
            button.getHeight() - yIndent * 2, 
            Justification::centred, 1, 1.f);
	}
}

void CustomLookAndFeel::drawPopupMenuBackground(Graphics& g, int width, int height)
{
	g.fillAll(findColour(PopupMenu::backgroundColourId));
	g.setColour(ColorPalette::monblack.withAlpha(0.6f));
	g.drawRect(0, 0, width, height);
}

void CustomLookAndFeel::drawPopupMenuItem(Graphics& g, const Rectangle<int>& area,
    const bool isSeparator, const bool isActive,
    const bool isHighlighted, const bool isTicked,
    const bool hasSubMenu, const String& text,
    const String& shortcutKeyText,
    [[maybe_unused]] const Drawable* icon, const Colour* const textColourToUse)
{
    if (isSeparator)
    {
        Rectangle<int> r(area.reduced(5, 0));
        r.removeFromTop(r.getHeight() / 2 - 1);

        g.setColour(Colour(0x33000000));
        g.fillRect(r.removeFromTop(1));

        g.setColour(Colour(0x66ffffff));
        g.fillRect(r.removeFromTop(1));
    }
    else
    {
        Colour textColour(findColour(PopupMenu::textColourId));

        if (textColourToUse != nullptr)
            textColour = *textColourToUse;

        Rectangle<int> r(area.reduced(1));

        if (isHighlighted)
        {
            g.setColour(findColour(PopupMenu::highlightedBackgroundColourId));
            g.fillRect(r);

            g.setColour(findColour(PopupMenu::highlightedTextColourId));
        }
        else
        {
            g.setColour(textColour);
        }

        if (!isActive)  g.setOpacity(0.3f);

        Font font(getPopupMenuFont());
        const float fontHeight = area.getHeight() * 0.45f;
        font.setHeight(fontHeight);
        g.setFont(font);

        if (isTicked)
        {
            g.setColour(ColorPalette::miamipink);   // Font colour if it's selected
        }

        if (hasSubMenu)
        {
            const float arrowH = 0.6f * getPopupMenuFont().getAscent();

            const float x = (float)r.removeFromRight((int)arrowH).getX();
            const float halfH = (float)r.getCentreY();

            Path p;
            p.addTriangle(x, halfH - arrowH * 0.5f,
                x, halfH + arrowH * 0.5f,
                x + arrowH * 0.6f, halfH);

            g.fillPath(p);
        }

        g.drawFittedText(text, r.reduced(5), Justification::centred, 1);

        if (shortcutKeyText.isNotEmpty())
        {
            Font f2(font);
            f2.setHeight(f2.getHeight() * 0.75f);
            f2.setHorizontalScale(0.95f);
            g.setFont(f2);

            g.drawText(shortcutKeyText, r, Justification::centredRight, true);
        }
    }
}

void CustomLookAndFeel::drawLabel(Graphics& g, Label& label)
{
    g.fillAll(label.findColour(Label::backgroundColourId));

    if (!label.isBeingEdited())
    {
        auto alpha = label.isEnabled() ? 1.0f : 0.5f;
        auto textArea = getLabelBorderSize(label).subtractedFrom(label.getLocalBounds());

        auto fontSize = textArea.getHeight() * 0.45;
        Font font(fontSize);

        const int stringLength = font.getStringWidth(label.getText());
        const int textAreaWidth = textArea.getWidth();

        if (stringLength > textAreaWidth)
        {
            float scaleFactor = static_cast<float>(textAreaWidth) / static_cast<float>(stringLength);
            fontSize *= scaleFactor;

            if (label.getFont().getHeight() > fontSize)
            {
                font.setHeight(label.getFont().getHeight());
            }
            else {
                font.setHeight(fontSize);
            }
        }

        g.setColour(label.findColour(Label::textColourId).withMultipliedAlpha(alpha));
        g.setFont(font);

        g.drawFittedText(label.getText(), textArea, label.getJustificationType(),
            jmax(1, (int)((float)textArea.getHeight() / font.getHeight())),
            label.getMinimumHorizontalScale());

        g.setColour(label.findColour(Label::outlineColourId).withMultipliedAlpha(alpha));
    }
    else if (label.isEnabled())
    {
        g.setColour(label.findColour(Label::outlineColourId));
    }
}

void CustomLookAndFeel::drawTitle(juce::Graphics& g, const juce::String& text, 
    juce::Rectangle<int> textArea, const juce::Justification justification, const float minFontSize, const float proportion)
{
    auto fontSize = textArea.getHeight() * proportion;
    Font font(fontSize);

    const int stringLength = font.getStringWidth(text);
    const int textAreaWidth = textArea.getWidth();

    if (stringLength > textAreaWidth)
    {
        float scaleFactor = static_cast<float>(textAreaWidth) / static_cast<float>(stringLength);
        fontSize *= scaleFactor;

        if (minFontSize > fontSize)
        {
            font.setHeight(minFontSize);
        }
        else {
            font.setHeight(fontSize);
        }
    }

    g.setFont(font);

    g.drawFittedText(text, textArea, justification,
        jmax(1, (int)((float)textArea.getHeight() / font.getHeight())),
        0.f);
}
