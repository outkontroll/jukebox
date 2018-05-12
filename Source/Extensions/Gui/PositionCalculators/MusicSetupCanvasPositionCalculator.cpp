#include "MusicSetupCanvasPositionCalculator.h"

using namespace jukebox::gui;
using namespace juce;

namespace {
    const int columns = 4;
    const int defaultImageOffsetX = 20;
    const int defaultOffsetY = 10;
}

MusicSetupCanvasPositionCalculator::MusicSetupCanvasPositionCalculator(int width_, int height_, float fontSize_) :
    width(width_),
    height(height_),
    fontSize(fontSize_),
    fontSizeInt(static_cast<int>(fontSize)),
    offsetX(static_cast<int>(width * 0.016f)),
    offsetY(static_cast<int>(height / 43.75f)),
    musicTextWidth(width / 5 * 2),
    imageWidth(width / columns - defaultImageOffsetX),
    imageHeight(imageWidth),
    imageBottom(offsetY * 2 + fontSizeInt + imageHeight),
    rightSideLeft(offsetX + static_cast<int>(width / 2 - offsetX * 2)),
    rightSideTextWidth(width - rightSideLeft - offsetX * 2)
{
}

juce::Rectangle<int> MusicSetupCanvasPositionCalculator::calculateInfoMusicDirectoryBounds() const
{
    const int xPosition = offsetX;
    const int yPosition = offsetY;

    const int infoWidth = offsetX * 8;
    const int infoHeight = fontSizeInt;

    return {xPosition, yPosition, infoWidth, infoHeight};
}

juce::Rectangle<int> MusicSetupCanvasPositionCalculator::calculateTextMusicDirectoryBounds() const
{
    const int xPosition = offsetX * 9;
    const int yPosition = offsetY;

    const int textHeight = fontSizeInt;

    return {xPosition, yPosition, musicTextWidth, textHeight};
}

juce::Rectangle<int> MusicSetupCanvasPositionCalculator::calculateButtonMusicDirectoryBounds() const
{
    const int xPosition = offsetX * 10 + musicTextWidth;
    const int yPosition = offsetY;

    const int buttonWidth = fontSizeInt * 3 / 2;
    const int buttonHeight = fontSizeInt;

    return {xPosition, yPosition, buttonWidth, buttonHeight};
}

juce::Rectangle<int> MusicSetupCanvasPositionCalculator::calculateTreeMusicDirectoryBounds() const
{
    const int xPosition = offsetX;
    const int yPosition = offsetY * 2 + fontSizeInt;

    const int treeWidth = width / 2 - offsetX * 2;
    const int treeHeight = height - offsetY * 4 - fontSizeInt * 2;

    return {xPosition, yPosition, treeWidth, treeHeight};
}

juce::Rectangle<int> MusicSetupCanvasPositionCalculator::calculateButtonImportBounds() const
{
    const int xPosition = offsetX;
    const int yPosition = offsetY * 2 + fontSizeInt + height - offsetY * 4 - fontSizeInt * 2 + offsetY;

    const int buttonWidth = static_cast<int>(width / 2 - offsetX * 2);
    const int buttonHeight = fontSizeInt;

    return {xPosition, yPosition, buttonWidth, buttonHeight};
}

juce::Rectangle<int> MusicSetupCanvasPositionCalculator::calculateImagePreviewBounds() const
{
    const int xPosition = (width - rightSideLeft - imageWidth) / 2 + rightSideLeft;
    const int yPosition = offsetY * 2 + fontSizeInt;

    return {xPosition, yPosition, imageHeight, imageHeight};
}

juce::Rectangle<int> MusicSetupCanvasPositionCalculator::calculateInfoArtistBounds() const
{
    const int xPosition = rightSideLeft + offsetX;
    const int yPosition = imageBottom + defaultOffsetY;
    return {xPosition, yPosition, rightSideTextWidth, fontSizeInt};
}

juce::Rectangle<int> MusicSetupCanvasPositionCalculator::calculateTextArtistBounds() const
{
    const int xPosition = rightSideLeft + offsetX;
    const int yPosition = imageBottom + defaultOffsetY * 2 + fontSizeInt;
    return {xPosition, yPosition, rightSideTextWidth, fontSizeInt};
}

juce::Rectangle<int> MusicSetupCanvasPositionCalculator::calculateInfoTitleBounds() const
{
    const int xPosition = rightSideLeft + offsetX;
    const int yPosition = imageBottom + defaultOffsetY * 3 + fontSizeInt * 2;
    return {xPosition, yPosition, rightSideTextWidth, fontSizeInt};
}

juce::Rectangle<int> MusicSetupCanvasPositionCalculator::calculateTextTitleBounds() const
{
    const int xPosition = rightSideLeft + offsetX;
    const int yPosition = imageBottom + defaultOffsetY * 4 + fontSizeInt * 3;
    return {xPosition, yPosition, rightSideTextWidth, fontSizeInt};
}

juce::Rectangle<int> MusicSetupCanvasPositionCalculator::calculateInfoSongsBounds() const
{
    const int xPosition = rightSideLeft + offsetX;
    const int yPosition = imageBottom + defaultOffsetY * 5 + fontSizeInt * 4;
    return {xPosition, yPosition, rightSideTextWidth, fontSizeInt};
}

juce::Rectangle<int> MusicSetupCanvasPositionCalculator::calculateTextSongsBounds() const
{
    const int xPosition = rightSideLeft + offsetX;
    const int yPosition = imageBottom + defaultOffsetY * 6 + fontSizeInt * 5;
    const int textHeight = height - yPosition - offsetY;

    return {xPosition, yPosition, rightSideTextWidth, textHeight};
}
