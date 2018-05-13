#include "SetupPageCanvasPositionCalculator.h"

using namespace jukebox::gui;
using namespace juce;

SetupPageCanvasPositionCalculator::SetupPageCanvasPositionCalculator(int width_, int height_, float fontSize_) :
    width(width_),
    height(height_),
    fontSize(fontSize_),
    fontSizeInt(static_cast<int>(fontSize_)),
    offsetX(static_cast<int>(width * 0.016f)),
    offsetY(static_cast<int>(height / 43.75f)),
    statisticsWidth(width / 3 * 2),
    statisticsHeight(height / 5 * 3),
    rightWidth(width - statisticsWidth - offsetX * 3)
{
}

juce::Rectangle<float> SetupPageCanvasPositionCalculator::calculateTextPlace() const
{
    const float xPosition = width / 2;
    const float yPosition = height / 3;
    const float textHeight = fontSize;
    const float textWidth = width;

    return { xPosition, yPosition, textWidth, textHeight };
}

juce::Rectangle<int> SetupPageCanvasPositionCalculator::calculateInfoStatisticsBounds() const
{
    const int xPosition = offsetX;
    const int yPosition = offsetY * 2 + fontSizeInt * 1;
    const int infoWidth = width / 4;

    return {xPosition, yPosition, infoWidth, fontSizeInt};
}

juce::Rectangle<int> SetupPageCanvasPositionCalculator::calculateTextStatisticsBounds() const
{
    const int xPosition = offsetX;
    const int yPosition = offsetY * 3 + fontSizeInt * 2;

    return {xPosition, yPosition, statisticsWidth, statisticsHeight};
}

juce::Rectangle<int> SetupPageCanvasPositionCalculator::calculateInfoTimeToPlayASong() const
{
    const int xPosition = offsetX;
    const int yPosition = offsetY * 4 + fontSizeInt * 2 + statisticsHeight;
    const int infoWidth = width / 3;

    return {xPosition, yPosition, infoWidth, fontSizeInt};
}

juce::Rectangle<int> SetupPageCanvasPositionCalculator::calculateComboTimeToPlayASong() const
{
    const int comboWidth = fontSizeInt * 10 / 6;
    const int xPosition = offsetX * 2 + statisticsWidth / 2 - comboWidth;
    const int yPosition = offsetY * 4 + fontSizeInt * 2 + statisticsHeight;

    return {xPosition, yPosition, comboWidth, fontSizeInt};
}

juce::Rectangle<int> SetupPageCanvasPositionCalculator::calculateInfoTimeToSaveInsertedCoins() const
{
    const int xPosition = offsetX;
    const int yPosition = offsetY * 5 + fontSizeInt * 3 + statisticsHeight;
    const int infoWidth = width / 3;

    return {xPosition, yPosition, infoWidth, fontSizeInt};
}

juce::Rectangle<int> SetupPageCanvasPositionCalculator::calculateComboTimeToSaveInsertedCoins() const
{
    const int comboWidth = fontSizeInt * 100 / 48;
    const int xPosition = offsetX * 2 + statisticsWidth / 2 - comboWidth;
    const int yPosition = offsetY * 5 + fontSizeInt * 3 + statisticsHeight;

    return {xPosition, yPosition, comboWidth, fontSizeInt};
}

juce::Rectangle<int> SetupPageCanvasPositionCalculator::calculateInfoTimeToPlayAdvertiseMusic() const
{
    const int xPosition = offsetX;
    const int yPosition = offsetY * 6 + fontSizeInt * 4 + statisticsHeight;
    const int infoWidth = width / 3;

    return {xPosition, yPosition, infoWidth, fontSizeInt};
}

juce::Rectangle<int> SetupPageCanvasPositionCalculator::calculateComboTimeToPlayAdvertiseMusic() const
{
    const int comboWidth = fontSizeInt * 100 / 48;
    const int xPosition = offsetX * 2 + statisticsWidth / 2 - comboWidth;
    const int yPosition = offsetY * 6 + fontSizeInt * 4 + statisticsHeight;

    return {xPosition, yPosition, comboWidth, fontSizeInt};
}

juce::Rectangle<int> SetupPageCanvasPositionCalculator::calculateNoPasswordToggleBounds() const
{
    const int xPosition = statisticsWidth + offsetX * 2;
    const int yPosition = statisticsHeight + offsetY * 1 - fontSizeInt;

    const int buttonWidth = rightWidth;
    const int buttonHeight = fontSizeInt;

    return {xPosition, yPosition, buttonWidth, buttonHeight};
}

juce::Rectangle<int> SetupPageCanvasPositionCalculator::calculatePasswordToggleBounds() const
{
    const int xPosition = statisticsWidth + offsetX * 2;
    const int yPosition = statisticsHeight + offsetY * 2;

    const int buttonWidth = rightWidth;
    const int buttonHeight = fontSizeInt;

    return {xPosition, yPosition, buttonWidth, buttonHeight};
}

juce::Rectangle<int> SetupPageCanvasPositionCalculator::calculateChangePasswordBounds() const
{
    const int xPosition = statisticsWidth + offsetX * 2;
    const int yPosition = statisticsHeight + offsetY * 3 + fontSizeInt;

    const int buttonWidth = rightWidth;
    const int buttonHeight = fontSizeInt;

    return {xPosition, yPosition, buttonWidth, buttonHeight};
}
