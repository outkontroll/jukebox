#include "SetupPagePositionCalculator.h"

using namespace jukebox::gui;
using namespace juce;

juce::Rectangle<float> SetupPagePositionCalculator::calculateTextPlace() const
{
    const float xPosition = width / 2;
    const float yPosition = height / 3;
    const float textHeight = fontSize;
    const float textWidth = width;

    return { xPosition, yPosition, textWidth, textHeight };
}

juce::Rectangle<int> SetupPagePositionCalculator::calculateChangePasswordBounds() const
{
    const int offsetX(static_cast<int>(width * 0.016f));
    const int canvasTop(static_cast<int>(height / 43.75f));

    const int xPosition = static_cast<int>(width / 2) + offsetX;
    const int yPosition = canvasTop;

    const int buttonWidth = static_cast<int>(fontSize) * 20;
    const int buttonHeight = static_cast<int>(fontSize);

    return {xPosition, yPosition, buttonWidth, buttonHeight};
}
