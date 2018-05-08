#include "MainComponentPositionCalculator.h"

MainComponentPositionCalculator::MainComponentPositionCalculator(int width_, int height_) :
    width(width_),
    height(height_),
    canvasLeft(width * 0.016),
    canvasTop(height / 43.75),
    canvasWidth(width * 0.76),
    canvasHeight(height * 0.89),
    offsetWidth(canvasLeft),
    offsetHeight(canvasTop),
    fontHeightBig(height * 0.04),
    fontHeightSmall(height * 0.0225),
    fontWidthBig(width * 0.014),
    sidePanelLeft(canvasLeft + canvasWidth + offsetWidth),
    sidePanelTop(offsetHeight),
    sidePanelWidth(width - sidePanelLeft - offsetWidth),
    statusTop(height * 0.92)
{
}

juce::Rectangle<int> MainComponentPositionCalculator::getCanvasBounds() const
{
    return {canvasLeft, canvasTop, canvasWidth, canvasHeight};
}

juce::Rectangle<int> MainComponentPositionCalculator::getLblAlbumNumberBounds() const
{
    return {sidePanelLeft, sidePanelTop, fontWidthBig * 3, fontHeightBig};
}

juce::Rectangle<int> MainComponentPositionCalculator::getLblSongNumberBounds() const
{
    return {sidePanelLeft + fontWidthBig * 3 + offsetWidth, sidePanelTop, fontWidthBig * 2, fontHeightBig};
}

juce::Rectangle<int> MainComponentPositionCalculator::getInfoCreditBounds() const
{
    return {sidePanelLeft, sidePanelTop + fontHeightBig + offsetHeight * 2, fontHeightBig * 7, fontHeightBig};
}

juce::Rectangle<int> MainComponentPositionCalculator::getLblCreditsBounds() const
{
    return {sidePanelLeft + sidePanelWidth - fontHeightBig * 4 - offsetWidth, sidePanelTop + fontHeightBig + offsetHeight * 2, fontHeightBig * 3, fontHeightBig};
}

juce::Rectangle<int> MainComponentPositionCalculator::getInfoCurrentSongBounds() const
{
    return {sidePanelLeft, sidePanelTop + fontHeightBig * 2 + offsetHeight * 4, sidePanelWidth, fontHeightSmall};
}

juce::Rectangle<int> MainComponentPositionCalculator::getTxtCurrentSongBounds() const
{
    return {sidePanelLeft, sidePanelTop + fontHeightBig * 2 + fontHeightSmall + offsetHeight * 5, sidePanelWidth, static_cast<int>(fontHeightSmall * 2.4)};
}

juce::Rectangle<int> MainComponentPositionCalculator::getInfoPlayQueueBounds() const
{
    return {sidePanelLeft, sidePanelTop + fontHeightBig * 2 + fontHeightSmall * 3 + offsetHeight * 11, sidePanelWidth, fontHeightBig};
}

juce::Rectangle<int> MainComponentPositionCalculator::getPlayQueueBounds() const
{
    return {sidePanelLeft, sidePanelTop + fontHeightBig * 3 + fontHeightSmall * 3 + offsetHeight * 12, sidePanelWidth, fontHeightSmall * 15};
}

juce::Rectangle<int> MainComponentPositionCalculator::getLblStatusBounds() const
{
    return {canvasLeft, statusTop, canvasWidth, fontHeightBig};
}

int MainComponentPositionCalculator::getFontHeigthBig() const
{
    return fontHeightBig;
}

int MainComponentPositionCalculator::getFontHeigthSmall() const
{
    return fontHeightSmall;
}
