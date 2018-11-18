#include "MultipleAlbumsCanvas.h"
#include <numeric>
#include "IFileSystem.h"
#include "Formaters.h"
#include "ResourceId.h"
#include "ResourceString.h"
#include "StdAddons.hpp"
#include "Song.h"
#include "MultipleAlbumsCanvasPositionCalculator.h"

using namespace jukebox::gui;
using namespace juce;

namespace {
    const float bigFontSize = 24.0f;
    const float selectionThickness = 4.0f;
}

void MultipleAlbumsCanvas::paint(Graphics& g)
{
    g.setColour(Colours::black);
    g.drawRect(Rectangle<int>{0, 0, getWidth(), getHeight()});

    g.setFont(bigFontSize);

    for(const auto& album : visibleAlbums)
    {
        // album's number
        g.drawText(jukebox::FillWithLeadingZeros(album.albumNumber, 3), album.position.textPlace, Justification::centredLeft);

        // album's image, if we can find one
        const auto& image = album.image;
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
    albumPositions.clear();
    visibleAlbums.clear();
    selectionPlaces.clear();

    slotWidth = static_cast<float>(getWidth()) / columns;
    slotHeight = static_cast<float>(getHeight()) / rows;

    MultipleAlbumsCanvasPositionCalculator positions(slotWidth, slotHeight, columns);

    std::vector<int> indexes(static_cast<size_t>(columns * rows));
    std::iota(indexes.begin(), indexes.end(), 0);

    albumPositions.reserve(indexes.size());
    visibleAlbums.reserve(indexes.size());
    selectionPlaces.reserve(indexes.size());

    std_addons::transform(indexes, std::back_inserter(albumPositions), [&positions](int visibleAlbumIndex){
        return AlbumPositionInfo{positions.calculateImagePlace(visibleAlbumIndex),
                                 positions.calculateTextPlace(visibleAlbumIndex)};
    });

    std_addons::transform(albumPositions, std::back_inserter(selectionPlaces), [&positions](const AlbumPositionInfo& position){
        return AlbumPositionInfo{positions.calculateSelectionPlace(position.imagePlace),
                                 positions.calculateSelectionPlace(position.textPlace)};
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
        selectionTextPlace = selectionPlaces[static_cast<size_t>(selectedPosition)].textPlace;
        selectionImagePlace = selectionPlaces[static_cast<size_t>(selectedPosition)].imagePlace;
    }

    repaint();
}

void MultipleAlbumsCanvas::changeLayout(int rows_, int columns_)
{
    rows = rows_;
    columns = columns_;

    parentSizeChanged();
}
