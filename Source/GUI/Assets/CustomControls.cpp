/*
  ==============================================================================

    CustomControls.cpp

  ==============================================================================
*/

#include "CustomControls.h"

//==============================================================================
CustomSliderWithLabel::CustomSliderWithLabel(juce::String name, juce::String suffix, SliderStyle sliderStyle, const int numDecimals) : cslValueLabelLnF(0.75f), cslNameLabelLnF(0.55f)
{
    this->sliderStyle = sliderStyle;
    this->numDecimals = numDecimals;
    if (suffix.isNotEmpty()) this->suffix = " " + suffix;

    setupSlider();
    addAndMakeVisible(slider);

    valueLabel.setFont(valueLabelFontHeight);
    valueLabel.setText(slider.getTextFromValue(slider.getValue()) + this->suffix, juce::dontSendNotification);
    addAndMakeVisible(valueLabel);

    nameLabel.setFont(nameLabelFontHeight);
    nameLabel.setText(name, juce::dontSendNotification);
    addAndMakeVisible(nameLabel);
}

CustomSliderWithLabel::~CustomSliderWithLabel()
{
    valueLabel.setLookAndFeel(nullptr);
    nameLabel.setLookAndFeel(nullptr);
}

void CustomSliderWithLabel::paint(juce::Graphics& g)
{  
    /*
    // Uncomment to debug

    g.setColour(juce::Colours::green);
    g.drawRect(getLocalBounds());

    switch (sliderStyle)
    {
    case Vertical:
        g.setColour(juce::Colours::red);
        g.drawRect(0, 0, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.80); // Slider

        g.setColour(juce::Colours::yellow);
        g.drawRect(0, getLocalBounds().getHeight() * 0.80, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.10);   // Name

        g.setColour(juce::Colours::purple);
        g.drawRect(0, getLocalBounds().getHeight() * 0.90, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.10);   // Value
        break;
    case Horizontal:
        g.setColour(juce::Colours::red);
        g.drawRect(0, 0, getLocalBounds().getWidth() * 0.15, getLocalBounds().getHeight());  // Name

        g.setColour(juce::Colours::yellow);
        g.drawRect(getLocalBounds().getWidth() * 0.15, 0, getLocalBounds().getWidth() * 0.2, getLocalBounds().getHeight()); // Value

        g.setColour(juce::Colours::purple);
        g.drawRect(getLocalBounds().getWidth() * 0.35, 0, getLocalBounds().getWidth() * 0.65, getLocalBounds().getHeight());    // Slider
        break;
    case HorizontalCompact:
        g.setColour(juce::Colours::red);
        g.drawRect(0, 0, getLocalBounds().getWidth() * 0.25, getLocalBounds().getHeight() * 0.5);   // Name

        g.setColour(juce::Colours::yellow);
        g.drawRect(0, getLocalBounds().getHeight() * 0.5, getLocalBounds().getWidth() * 0.25, getLocalBounds().getHeight() * 0.5);  // Value

        g.setColour(juce::Colours::purple);
        g.drawRect(getLocalBounds().getWidth() * 0.25, 0, getLocalBounds().getWidth() * 0.75, getLocalBounds().getHeight());    // Slider
        break;
    default:
        g.setColour(juce::Colours::red);
        g.drawRect(0, 0, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.80);

        g.setColour(juce::Colours::yellow);
        g.drawRect(0, getLocalBounds().getHeight() * 0.80, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.10);

        g.setColour(juce::Colours::purple);
        g.drawRect(0, getLocalBounds().getHeight() * 0.90, getLocalBounds().getWidth(), getLocalBounds().getHeight() * 0.10);
        break;
    }
    */
}

void CustomSliderWithLabel::resized()
{
    auto localBounds = getLocalBounds();

    switch (sliderStyle)
    {
    case Vertical:
        nameLabel.setBounds(0, localBounds.getHeight() * 0.90, localBounds.getWidth(), localBounds.getHeight() * 0.10);
        valueLabel.setBounds(0, localBounds.getHeight() * 0.80, localBounds.getWidth(), localBounds.getHeight() * 0.10);
        slider.setBounds(0, 0, localBounds.getWidth(), localBounds.getHeight() * 0.80);
        break;
    case Horizontal:
        nameLabel.setBounds(0, 0, localBounds.getWidth() * 0.15, localBounds.getHeight());
        valueLabel.setBounds(localBounds.getWidth() * 0.15, 0, localBounds.getWidth() * 0.20, localBounds.getHeight());
        slider.setBounds(localBounds.getWidth() * 0.35, 0, localBounds.getWidth() * 0.65, localBounds.getHeight());
 
        cslNameLabelLnF.setFontLabelHeightRatio(0.7f);

        break;
    case HorizontalCompact:
        nameLabel.setBounds(0, localBounds.getHeight() * 0.5, localBounds.getWidth() * 0.25, localBounds.getHeight() * 0.5);
        valueLabel.setBounds(0, 0, localBounds.getWidth() * 0.25, localBounds.getHeight() * 0.5);
        slider.setBounds(localBounds.getWidth() * 0.25, 0, localBounds.getWidth() * 0.75, localBounds.getHeight());
        break;
    default:
        nameLabel.setBounds(0, localBounds.getHeight() * 0.90, localBounds.getWidth(), localBounds.getHeight() * 0.10);
        valueLabel.setBounds(0, localBounds.getHeight() * 0.80, localBounds.getWidth(), localBounds.getHeight() * 0.10);
        slider.setBounds(0, 0, localBounds.getWidth(), localBounds.getHeight() * 0.80);
        break;
    }
}

void CustomSliderWithLabel::updateValueLabel()
{
    valueLabel.setText(slider.getTextFromValue(slider.getValue()) + suffix, juce::dontSendNotification);
}

void CustomSliderWithLabel::setupSlider()
{
    valueLabel.setLookAndFeel(&cslValueLabelLnF);
    nameLabel.setLookAndFeel(&cslNameLabelLnF);

    switch (sliderStyle)
    {
    case Vertical:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        valueLabel.setJustificationType(juce::Justification::centredBottom);
        nameLabel.setJustificationType(juce::Justification::centredTop);
        break;
    case Horizontal:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
        valueLabel.setJustificationType(juce::Justification::centred);
        nameLabel.setJustificationType(juce::Justification::centred);
        break;
    case HorizontalCompact:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
        valueLabel.setJustificationType(juce::Justification::centredBottom);
        nameLabel.setJustificationType(juce::Justification::centredTop);
        break;
    default:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        valueLabel.setJustificationType(juce::Justification::centredBottom);
        nameLabel.setJustificationType(juce::Justification::centredTop);
    }

    slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    slider.setNumDecimalPlacesToDisplay(numDecimals);

    slider.onValueChange = [this] { 
        updateValueLabel(); 
    };
}

void CustomSliderWithLabel::applyBypassedColorPalette(const bool bypassed)
{
    if (bypassed)
    {
        valueLabel.setColour(juce::Label::ColourIds::textColourId, ColorPalette::bypassgrey);
        slider.setColour(juce::Slider::ColourIds::backgroundColourId, ColorPalette::bypassgrey);
        slider.setColour(juce::Slider::ColourIds::trackColourId, ColorPalette::bypassgrey);
        slider.setColour(juce::Slider::ColourIds::thumbColourId, ColorPalette::bypassgrey);
    } 
    else 
    {
        valueLabel.setColour(juce::Label::ColourIds::textColourId, ColorPalette::monwhite);
        slider.setColour(juce::Slider::ColourIds::backgroundColourId, ColorPalette::orthzul);
        slider.setColour(juce::Slider::ColourIds::trackColourId, ColorPalette::miamipink);
        slider.setColour(juce::Slider::ColourIds::thumbColourId, ColorPalette::miamiblue);
    }
}

// CustomSliderWithLabel LnF methods
void CustomSliderWithLabel::CustomSliderWithLabelLnF::drawLabel(juce::Graphics& g, juce::Label& label)
{
    g.fillAll(label.findColour(Label::backgroundColourId));

    if (!label.isBeingEdited())
    {
        auto alpha = label.isEnabled() ? 1.0f : 0.5f;
        auto textArea = getLabelBorderSize(label).subtractedFrom(label.getLocalBounds());

        auto fontSize = textArea.getHeight() * fontLabelHeightRatio;
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

// CustomBypassButton LnF methods
void CustomBypassButton::BypassButtonLnF::drawToggleButton(juce::Graphics& g,
    juce::ToggleButton& toggleButton,
    bool shouldDrawButtonAsHighlighted,
    bool shouldDrawButtonAsDown)
{
    auto buttonBounds = toggleButton.getLocalBounds();
    auto buttonSize = juce::jmin(buttonBounds.getWidth(), buttonBounds.getHeight());
    auto circleBorder = buttonBounds.withSizeKeepingCentre(buttonSize, buttonSize).toFloat();
    buttonSize -= 6;

    float angleInDegrees = 30.f;

    juce::Path powerButtonShape;
    powerButtonShape.addCentredArc(circleBorder.getCentreX(),
        circleBorder.getCentreY(),
        buttonSize * 0.5,
        buttonSize * 0.5,
        0.f,
        degreesToRadians(angleInDegrees),
        degreesToRadians(360.f - angleInDegrees),
        true);

    powerButtonShape.startNewSubPath(circleBorder.getCentreX(), circleBorder.getY());
    powerButtonShape.lineTo(circleBorder.getCentre());

    juce::PathStrokeType pst(2.5f, juce::PathStrokeType::JointStyle::curved);

    auto buttonColour = toggleButton.getToggleState() ? ColorPalette::bypassgrey : ColorPalette::monwhite;

    g.setColour(buttonColour);
    g.strokePath(powerButtonShape, pst);

    //g.drawEllipse(circleBorder, 2.f);
}
