#include "MusicSetupCanvasPositionCalculator.h"

using namespace jukebox::gui;
using namespace juce;

namespace {
    const int columns = 4;
    const int defaultImageOffsetX = 20;
}

MusicSetupCanvasPositionCalculator::MusicSetupCanvasPositionCalculator(int width_, int height_, float fontSize_) :
    width(width_),
    height(height_),
    fontSize(fontSize_),
    offsetX(static_cast<int>(width * 0.016f)),
    offsetY(static_cast<int>(height / 43.75f)),
    textWidth(width / 5 * 2)
{
}

juce::Rectangle<int> MusicSetupCanvasPositionCalculator::calculateInfoMusicDirectoryBounds() const
{
    const int xPosition = offsetX;
    const int yPosition = offsetY;

    const int infoWidth = offsetX * 8;
    const int infoHeight = static_cast<int>(fontSize);

    return {xPosition, yPosition, infoWidth, infoHeight};
}

juce::Rectangle<int> MusicSetupCanvasPositionCalculator::calculateTextMusicDirectoryBounds() const
{
    const int xPosition = offsetX * 9;
    const int yPosition = offsetY;

    const int textHeight = static_cast<int>(fontSize);

    return {xPosition, yPosition, textWidth, textHeight};
}

juce::Rectangle<int> MusicSetupCanvasPositionCalculator::calculateButtonMusicDirectoryBounds() const
{
    const int xPosition = offsetX * 10 + textWidth;
    const int yPosition = offsetY;

    const int buttonWidth = static_cast<int>(fontSize * 3 / 2);
    const int buttonHeight = static_cast<int>(fontSize);

    return {xPosition, yPosition, buttonWidth, buttonHeight};
}

juce::Rectangle<int> MusicSetupCanvasPositionCalculator::calculateTreeMusicDirectoryBounds() const
{
    const int xPosition = offsetX;
    const int yPosition = offsetY * 2 + static_cast<int>(fontSize);

    const int treeWidth = static_cast<int>(width / 2 - offsetX * 2);
    const int treeHeight = static_cast<int>(height - offsetY * 4 - fontSize * 2);

    return {xPosition, yPosition, treeWidth, treeHeight};
}

juce::Rectangle<int> MusicSetupCanvasPositionCalculator::calculateButtonImportBounds() const
{
    const int xPosition = offsetX;
    const int yPosition = offsetY * 2 + static_cast<int>(fontSize) + static_cast<int>(height - offsetY * 4 - fontSize * 2) + offsetY;

    const int buttonWidth = static_cast<int>(width / 2 - offsetX * 2);
    const int buttonHeight = static_cast<int>(fontSize);

    return {xPosition, yPosition, buttonWidth, buttonHeight};
}

juce::Rectangle<int> MusicSetupCanvasPositionCalculator::calculateImagePreviewBounds() const
{
    const int slotWidth = width / columns;

    const int imageWidth = slotWidth - defaultImageOffsetX;
    const int imageHeight = imageWidth;

    const int xEndOfTree = offsetX + static_cast<int>(width / 2 - offsetX * 2);
    const int xPosition = (width - xEndOfTree - imageWidth) / 2 + xEndOfTree;
    const int yPosition = offsetY * 2 + static_cast<int>(fontSize);

    return {xPosition, yPosition, imageHeight, imageHeight};
}
