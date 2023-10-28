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
		g.drawFittedText(button.getButtonText(), leftIndent, yIndent, textWidth, button.getHeight() - yIndent * 2, Justification::centred, 1, 1.f);
	}
}
