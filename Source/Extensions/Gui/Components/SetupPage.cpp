#include "SetupPage.h"

using namespace jukebox::gui;
using namespace juce;

namespace {
    const float bigFontSize = 24.0f;
    const char* setupPageName = "Setup";
}

void SetupPage::paint(Graphics &g)
{
    //TODO just for testing purposes
    g.setColour(Colours::aliceblue);
    g.drawRect(Rectangle<int>{0, 0, getWidth(), getHeight()});
    //END TODO

    g.setColour(Colours::black);

    auto currentFont = g.getCurrentFont();
    currentFont.setHeight(bigFontSize);
    g.setFont(currentFont);

    // album's number
    g.drawText(setupPageName, textPlace, Justification::centredLeft);
}

void SetupPage::parentSizeChanged()
{
    textPlace = calculateTextPlace(getWidth(), getHeight());
}

juce::Rectangle<float> SetupPage::calculateTextPlace(float width, float height) const
{
    const float xPosition = width / 2;
    const float yPosition = height / 3;
    const float textHeight = bigFontSize;
    const float textWidth = width;

    return { xPosition, yPosition, textWidth, textHeight };
}
