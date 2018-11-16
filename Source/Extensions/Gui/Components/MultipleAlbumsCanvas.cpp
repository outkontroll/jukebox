#include "MultipleAlbumsCanvas.h"
#include <numeric>
#include "IFileSystem.h"
#include "Formaters.h"
#include "ResourceId.h"
#include "ResourceString.h"
#include "StdAddons.hpp"
#include "Song.h"

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

void MultipleAlbumsCanvas::paint(Graphics& g)
{
    g.setColour(Colours::black);
    g.drawRect(Rectangle<int>{0, 0, getWidth(), getHeight()});

    g.setFont(bigFontSize);

    for(const auto& album : visibleAlbums)
    {
        const auto& image = album.image;

        // album's number
        g.drawText(jukebox::FillWithLeadingZeros(album.albumNumber, 3), album.position.textPlace, Justification::centredLeft);

        // album's image, if we can find one
        if(image.isValid())
        {
            g.drawImage(image, album.position.imagePlace, RectanglePlacement::stretchToFit);
        }
        else
        {
            g.drawText(Resources::getResourceStringFromId(ResourceId::ErrorImageNotFound), album.position.imagePlace, Justification::centred );
        }

        // selection frame (if this is the selected album)
        if(album.albumNumber == selectedAlbumIndex)
        {
            g.setColour(Colours::yellow);

            g.drawRect(selectionImagePlace, selectionThickness);

            g.drawRect(selectionTextPlace, selectionThickness);

            g.setColour(Colours::black);
        }
    }
}

void MultipleAlbumsCanvas::parentSizeChanged()
{
    slotWidth = static_cast<float>(getWidth()) / columns;
    slotHeight = static_cast<float>(getHeight()) / rows;

    std::vector<int> indexes(static_cast<size_t>(columns * rows));
    std::iota(indexes.begin(), indexes.end(), 0);

    albumPositions.reserve(indexes.size());
    visibleAlbums.reserve(indexes.size());

    std_addons::transform(indexes, std::back_inserter(albumPositions), [this](int visibleAlbumIndex){
        const auto position = getPositionFromIndex(visibleAlbumIndex);
        return AlbumPositionInfo{calculateImagePlace(position, slotWidth, slotHeight),
                                 calculateTextPlace(position, slotWidth, slotHeight)};
    });
}

void MultipleAlbumsCanvas::loadAlbums(const std::vector<jukebox::audio::AlbumInfo>& albums, int firstAlbumIndex)
{
    visibleAlbums.clear();

    if(albums.empty())
        return;

    int albumIndex = firstAlbumIndex;
    const auto start = albums.begin() + (firstAlbumIndex - 1);
    const auto stop = (static_cast<int>(std::distance(start, albums.end())) < columns * rows) ? albums.end() : start + columns * rows;
    std::transform(start, stop, albumPositions.begin(), std::back_inserter(visibleAlbums), [&](const jukebox::audio::AlbumInfo& album, const AlbumPositionInfo& albumPosition) -> VisibleAlbum {
        const auto image = ImageFileFormat::loadFrom(File(album.imagePath));
        return {image, albumPosition, albumIndex++};
    });
}

void MultipleAlbumsCanvas::setSelection(int selectedIndex)
{
    selectedAlbumIndex = selectedIndex;
    if(!visibleAlbums.empty())
    {
        const auto selectedPosition = selectedAlbumIndex - visibleAlbums.begin()->albumNumber;
        selectionTextPlace = calculateSelectionPlace(visibleAlbums[static_cast<size_t>(selectedPosition)].position.textPlace);
        selectionImagePlace = calculateSelectionPlace(visibleAlbums[static_cast<size_t>(selectedPosition)].position.imagePlace);
    }

    repaint();
}

void MultipleAlbumsCanvas::changeLayout(int rows_, int columns_)
{
    rows = rows_;
    columns = columns_;
}

Rectangle<float> MultipleAlbumsCanvas::calculateImagePlace(Position position, float slotWidth_, float slotHeight_) const
{
    const float imageWidth = slotWidth_ - defaultImageOffsetX;
    const float imageHeight = imageWidth;

    return { slotWidth_ * position.x + (slotWidth_ - imageWidth) / 2,
             slotHeight_ * position.y + (slotHeight_ - imageHeight) / imageOffsetYMultiplier,
             imageWidth,
             imageHeight };
}

Rectangle<float> MultipleAlbumsCanvas::calculateTextPlace(Position position, float slotWidth_, float slotHeight_) const
{
    const float textHeight = bigFontSize;
    const float textWidth = albumNumberTextWidth;
    const float imageWidth = slotWidth_ - defaultImageOffsetX;

    return { slotWidth_ * position.x + (slotWidth_ - imageWidth) / 2 + defaultTextOffsetX,
             slotHeight_ * position.y + defaultTextOffsetY,
             textWidth,
             textHeight };
}

Rectangle<float> MultipleAlbumsCanvas::calculateSelectionPlace(const Rectangle<float>& placeToSelect)
{
    return { placeToSelect.getX() - selectionThickness,
             placeToSelect.getY() - selectionThickness,
             placeToSelect.getWidth() + 2 * selectionThickness,
             placeToSelect.getHeight() + 2 * selectionThickness };
}

MultipleAlbumsCanvas::Position MultipleAlbumsCanvas::getPositionFromIndex(int index) const
{
    return { index % columns, index / columns };
}
