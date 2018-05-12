#include "SetupPagePositionCalculator.h"

using namespace jukebox::gui;
using namespace juce;

SetupPagePositionCalculator::SetupPagePositionCalculator(int width_, int height_, float fontSize_) :
    width(width_),
    height(height_),
    fontSize(fontSize_),
    offsetX(static_cast<int>(width * 0.016f)),
    offsetY(static_cast<int>(height / 43.75f)),
    statisticsWidth(width / 3 * 2),
    statisticsHeight(height / 5 * 3),
    rightWidth(width - statisticsWidth - offsetX * 3)
{
}

juce::Rectangle<float> SetupPagePositionCalculator::calculateTextPlace() const
{
    const float xPosition = width / 2;
    const float yPosition = height / 3;
    const float textHeight = fontSize;
    const float textWidth = width;

    return { xPosition, yPosition, textWidth, textHeight };
}

juce::Rectangle<int> SetupPagePositionCalculator::calculateStatisticsBounds() const
{
    const int xPosition = offsetX;
    const int yPosition = offsetY * 3 + static_cast<int>(fontSize) * 2;

    return {xPosition, yPosition, statisticsWidth, statisticsHeight};
}

juce::Rectangle<int> SetupPagePositionCalculator::calculateNoPasswordToggleBounds() const
{
    const int xPosition = statisticsWidth + offsetX * 2;
    const int yPosition = statisticsHeight + offsetY * 1 - static_cast<int>(fontSize);

    const int buttonWidth = rightWidth;
    const int buttonHeight = static_cast<int>(fontSize);

    return {xPosition, yPosition, buttonWidth, buttonHeight};
}

juce::Rectangle<int> SetupPagePositionCalculator::calculatePasswordToggleBounds() const
{
    const int xPosition = statisticsWidth + offsetX * 2;
    const int yPosition = statisticsHeight + offsetY * 2;

    const int buttonWidth = rightWidth;
    const int buttonHeight = static_cast<int>(fontSize);

    return {xPosition, yPosition, buttonWidth, buttonHeight};
}

juce::Rectangle<int> SetupPagePositionCalculator::calculateChangePasswordBounds() const
{
    const int xPosition = statisticsWidth + offsetX * 2;
    const int yPosition = statisticsHeight + offsetY * 3 + static_cast<int>(fontSize);

    const int buttonWidth = rightWidth;
    const int buttonHeight = static_cast<int>(fontSize);

    return {xPosition, yPosition, buttonWidth, buttonHeight};
}

