#include "MultipleAlbumsCanvasPositionCalculator.h"

using namespace jukebox::gui;
using namespace juce;

namespace {
    const float bigFontSize = 24.0f;
    const float albumNumberTextWidth = 35.0f;
    const float defaultImageOffsetX = 20.0f;
    const float defaultTextOffsetX = 10.0f;
    const float defaultTextOffsetY = 10.0f;
    const float imageOffsetYMultiplier = 1.8f;
    const float selectionThickness = 4.0f;
}

MultipleAlbumsCanvasPositionCalculator::MultipleAlbumsCanvasPositionCalculator(float slotWidth_, float slotHeight_, int columns_) :
    slotWidth(slotWidth_),
    slotHeight(slotHeight_),
    columns(columns_),
    imageWidth(slotWidth - defaultImageOffsetX)
{
}

Rectangle<float> MultipleAlbumsCanvasPositionCalculator::calculateImagePlace(int albumIndex) const
{
    const float imageHeight = imageWidth;
    const auto position = getPositionFromIndex(albumIndex);

    return { slotWidth * position.x + (slotWidth - imageWidth) / 2,
             slotHeight * position.y + (slotHeight - imageHeight) / imageOffsetYMultiplier,
             imageWidth,
             imageHeight };
}

Rectangle<float> MultipleAlbumsCanvasPositionCalculator::calculateTextPlace(int albumIndex) const
{
    const float textHeight = bigFontSize;
    const float textWidth = albumNumberTextWidth;
    const auto position = getPositionFromIndex(albumIndex);

    return { slotWidth * position.x + (slotWidth - imageWidth) / 2 + defaultTextOffsetX,
             slotHeight * position.y + defaultTextOffsetY,
             textWidth,
             textHeight };
}

Rectangle<float> MultipleAlbumsCanvasPositionCalculator::calculateSelectionPlace(const Rectangle<float>& placeToSelect)
{
    return { placeToSelect.getX() - selectionThickness,
             placeToSelect.getY() - selectionThickness,
             placeToSelect.getWidth() + 2 * selectionThickness,
             placeToSelect.getHeight() + 2 * selectionThickness };
}

MultipleAlbumsCanvasPositionCalculator::Position MultipleAlbumsCanvasPositionCalculator::getPositionFromIndex(int index) const
{
    return { index % columns, index / columns };
}
