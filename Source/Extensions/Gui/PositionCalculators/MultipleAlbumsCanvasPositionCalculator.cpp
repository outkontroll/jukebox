#include "MultipleAlbumsCanvasPositionCalculator.h"

using namespace jukebox::gui;
using namespace juce;

namespace {

constexpr auto fontFactor = 14.1875f;
constexpr auto albumNumberTextWidth = 35.0f;
constexpr auto defaultImageOffsetX = 20.0f;
constexpr auto defaultTextOffsetX = 10.0f;
constexpr auto defaultTextOffsetY = 10.0f;
constexpr auto imageOffsetYDivisor = 1.8f;
constexpr auto selectionThicknessFactor = 64.75f;


constexpr auto imageScale = 0.94f;
constexpr auto x1Scale = 3.0f / 10.0f;
constexpr auto x2Scale = 3.0f / 10.0f;
constexpr auto textScale = 4.0f / 10.0f;
}

MultipleAlbumsPositionCalculator::MultipleAlbumsPositionCalculator(float slotWidth_, float slotHeight_, int columns_) :
    slotWidth(slotWidth_),
    slotHeight(slotHeight_),
    columns(columns_),
    outerOffsets(calculateOuterOffsets(slotWidth, slotHeight)),
    innerOffsets(calculateInnerOffsets(outerOffsets)),
    imageSize(slotWidth - defaultImageOffsetX),
    textSize(slotHeight / fontFactor),
    selectionThickness(slotWidth / selectionThicknessFactor)
{
}

juce::Rectangle<float> MultipleAlbumsPositionCalculator::calculateImagePlace(int albumIndex) const
{
    const auto position = getPositionFromIndex(albumIndex);

    return {slotWidth * position.x + outerOffsets.e + innerOffsets.z,
            slotHeight * position.y + outerOffsets.f + innerOffsets.x1 + innerOffsets.t + innerOffsets.x2,
            innerOffsets.p,
            innerOffsets.p};
}

Rectangle<float> MultipleAlbumsPositionCalculator::calculateTextPlace(int albumIndex) const
{
    const float textHeight = textSize;
    const float textWidth = albumNumberTextWidth;
    const auto position = getPositionFromIndex(albumIndex);

    return { slotWidth * position.x + (slotWidth - imageSize) / 2 + defaultTextOffsetX,
             slotHeight * position.y + defaultTextOffsetY,
             textWidth,
                textHeight };
}

juce::Rectangle<float> MultipleAlbumsPositionCalculator::calculateTextPlace2(int albumIndex) const
{
    const auto position = getPositionFromIndex(albumIndex);

    return {slotWidth * position.x + outerOffsets.e + innerOffsets.z * 2,
            slotHeight * position.y + outerOffsets.f + innerOffsets.x1 - innerOffsets.t * 0.2f,
                //TODO innerOffsets
            innerOffsets.t * 1.5f,
            innerOffsets.t};
}

Rectangle<float> MultipleAlbumsPositionCalculator::calculateSelectionPlace(const Rectangle<float>& placeToSelect)
{
    return { placeToSelect.getX() - selectionThickness,
             placeToSelect.getY() - selectionThickness,
             placeToSelect.getWidth() + 2 * selectionThickness,
                placeToSelect.getHeight() + 2 * selectionThickness };
}
//TODO
juce::Rectangle<float> MultipleAlbumsPositionCalculator::calculateSlot(int albumIndex) const
{
    const auto position = getPositionFromIndex(albumIndex);
    return {slotWidth * position.x, slotHeight * position.y, slotWidth, slotHeight};
}

MultipleAlbumsPositionCalculator::Position MultipleAlbumsPositionCalculator::getPositionFromIndex(int index) const
{
    return { index % columns, index / columns };
}

MultipleAlbumsPositionCalculator::OuterOffsets MultipleAlbumsPositionCalculator::calculateOuterOffsets(float width, float height) const
{
    const auto heightPercentage = 1.2f;
    const auto threshold = 1e-4f;
    const auto difference = (width * heightPercentage - height);

    if(fabs(difference) < threshold) //w * 1.2 == h
    {
        const auto a = width;
        const auto b = height;
        const auto e = 0;
        const auto f = 0;

        return {a, b, e, f};
    }
    else if(width * heightPercentage > height) //w * 1.2 > h
    {
        const auto a = height / heightPercentage;
        const auto b = height;
        const auto e = (width - a) / 2;
        const auto f = 0;

        return {a, b, e, f};
    }
    else //w * 1.2 < h
    {
        const auto a = width;
        const auto b = a * heightPercentage;
        const auto e = 0;
        const auto f = (height - b) / 2;

        return {a, b, e, f};
    }
}

MultipleAlbumsPositionCalculator::InnerOffsets MultipleAlbumsPositionCalculator::calculateInnerOffsets(MultipleAlbumsPositionCalculator::OuterOffsets outerOffsets) const
{
    const auto p = outerOffsets.a * imageScale;
    const auto y = (outerOffsets.a - p) / 2;
    const auto z = y;
    const auto k = outerOffsets.b - p - y;
    const auto x1 = k * x1Scale;
    const auto t = k * textScale;
    const auto x2 = k * x2Scale;

    return {p, x1, x2, t, y, z};
}
