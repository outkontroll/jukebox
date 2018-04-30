#include "SingleAlbumPositionCalculator.h"
#include <algorithm>

using namespace jukebox::gui;
using namespace juce;

namespace {
    const float offsetXRatio = 0.963f;
    const float defaultTextOffsetX = 10.0f;
    const float defaultTextOffsetY = 10.0f;
    const float bigFontSize = 24.0f;
    const float offsetX = 4.0f;
    const float offsetY = 3.0f;
}

SingleAlbumPositionCalculator::SingleAlbumPositionCalculator(float width_, float height_, float imageSize_)
    : width(width_),
      height(height_),
      imageSize(imageSize_)
{}


Rectangle<float> SingleAlbumPositionCalculator::calculateImagePlace() const
{
    const float xPosition = (width / 2 - imageSize * offsetXRatio) / 2;
    const float yPosition = (height - imageSize) / 2;
    return { xPosition, yPosition, imageSize, imageSize };
}

Rectangle<float> SingleAlbumPositionCalculator::calculateAlbumTextPlace() const
{
    const float xPosition = (width / 2 - imageSize * offsetXRatio) / 2 + defaultTextOffsetX;
    const float textHeight = bigFontSize;
    const float textWidth = width;

    return { xPosition, defaultTextOffsetY, textWidth, textHeight };
}

Rectangle<float> SingleAlbumPositionCalculator::calculateArtistTextPlace() const
{
    const float xPosition = (width / 2 - imageSize * offsetXRatio) / 2 + defaultTextOffsetX + imageSize;
    const float textHeight = bigFontSize;
    const float textWidth = width / 2;

    return { xPosition, defaultTextOffsetX, textWidth, textHeight };
}

std::array<int, 3> SingleAlbumPositionCalculator::calculateDrawableSongNamesPlace() const
{
    const int startX = static_cast<int>((width / 2 - imageSize * offsetXRatio) / 2 + defaultTextOffsetX + imageSize);
    const int baseLineY = static_cast<int>((height - imageSize) / 2);
    const int maximumLineWidth = static_cast<int>(width - startX - defaultTextOffsetX);

    return { startX, baseLineY, maximumLineWidth };
}

std::vector<Rectangle<float>> SingleAlbumPositionCalculator::calculateSelectionBounds(const std::vector<String>& lines, std::array<int, 3> position) const
{
    const Font font(bigFontSize);
    std::vector<int> lineCounts(lines.size());

    std::transform(lineCounts.begin(), lineCounts.end(), lines.begin(), lineCounts.begin(), [&](int, const String& line){
        return (font.getStringWidth(line) / position[2]) + 1;
    });

    GlyphArrangement glyphArrangement;
    glyphArrangement.addJustifiedText (font,
                                       "0",
                                       static_cast<float>(position[0]),
                                       static_cast<float>(position[1]),
                                       static_cast<float>(position[2]),
                                       Justification::left);

    std::vector<float> selectionTopPositions;
    selectionTopPositions.reserve(lines.size());

    float currentHeight = glyphArrangement.getGlyph(0).getBounds().getTopLeft().getY();
    std::transform(lineCounts.begin(), lineCounts.end(), std::back_inserter(selectionTopPositions), [&currentHeight](int lineCount){
        const float currentTop = currentHeight;
        currentHeight += lineCount * bigFontSize;
       return currentTop;
    });

    std::vector<Rectangle<float>> selectionPositions;
    selectionPositions.reserve(lines.size());

    unsigned int currentLineIndex = 0;

    std::transform(selectionTopPositions.begin(), selectionTopPositions.end(), std::back_inserter(selectionPositions), [&](int topOfLine) -> Rectangle<float> {
        const Point<float> selectionTopLeft = {static_cast<float>(position[0]) - offsetX,
                                               topOfLine - offsetY};
        const Point<float> selectionBottomRight = {static_cast<float>(position[0]) + position[2] + offsetX,
                                                   topOfLine + lineCounts[currentLineIndex++] * bigFontSize + offsetY};

        return {selectionTopLeft, selectionBottomRight};
    });

    return selectionPositions;
}
