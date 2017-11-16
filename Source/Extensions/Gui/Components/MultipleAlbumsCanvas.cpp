#include "MultipleAlbumsCanvas.h"
#include "FileSystem.h"
#include "Formaters.h"
#include "ResourceId.h"
#include "ResourceString.h"

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
    //TODO just for testing purposes
    g.drawRect(Rectangle<int>{0, 0, getWidth(), getHeight()});

    g.setColour(Colours::black);

    auto currentFont = g.getCurrentFont();
    currentFont.setHeight(bigFontSize);
    g.setFont(currentFont);

    int onScreenindex(0);
    std::for_each(albums.begin(), albums.end(), [&g, &onScreenindex, this](const auto& album){
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

        ++onScreenindex;
    });
}

void MultipleAlbumsCanvas::parentSizeChanged()
{
    slotWidth = static_cast<float>(getWidth() / columns);
    slotHeight = static_cast<float>(getHeight() / rows);
    for(int visibleAlbumIndex = 0; visibleAlbumIndex < columns * rows; ++visibleAlbumIndex)
    {
        const auto position = getPositionFromIndex(visibleAlbumIndex);
        albumPositions.push_back({calculateImagePlace(position, slotWidth, slotHeight),
                                  calculateTextPlace(position, slotWidth, slotHeight)});
    }
}

void MultipleAlbumsCanvas::loadAlbums(const std::string& musicDirectoy, int firstAlbumIndex)
{
    albums.clear();

    std::accumulate(albumPositions.begin(), albumPositions.end(), firstAlbumIndex, [&, this](int albumIndex, const auto& albumPosition){
        const auto imagePath = jukebox::filesystem::FileSystem::getPicturePath(musicDirectoy, albumIndex, ".jpg");
        const auto image = ImageFileFormat::loadFrom(File(imagePath));

        albums.push_back({image, albumPosition, albumIndex});

        return ++albumIndex;
    });
}

void MultipleAlbumsCanvas::setSelection(int selectedIndex)
{
    selectedAlbumIndex = selectedIndex;
    if(!albums.empty())
    {
        const auto selectedPosition = selectedAlbumIndex - albums.begin()->albumNumber;
        selectionTextPlace = calculateSelectionPlace(albums[selectedPosition].position.textPlace);
        selectionImagePlace = calculateSelectionPlace(albums[selectedPosition].position.imagePlace);
    }

    repaint();
}

Rectangle<float> MultipleAlbumsCanvas::calculateImagePlace(Position position, float slotWidth, float slotHeight) const
{
    const float imageWidth = slotWidth - defaultImageOffsetX;
    const float imageHeight = imageWidth;

    return { slotWidth * position.x + (slotWidth - imageWidth) / 2,
             slotHeight * position.y + (slotHeight - imageHeight) / imageOffsetYMultiplier,
             imageWidth,
             imageHeight };
}

Rectangle<float> MultipleAlbumsCanvas::calculateTextPlace(Position position, float slotWidth, float slotHeight) const
{
    const float textHeight = bigFontSize;
    const float textWidth = albumNumberTextWidth;
    const float imageWidth = slotWidth - defaultImageOffsetX;

    return { slotWidth * position.x + (slotWidth - imageWidth) / 2 + defaultTextOffsetX,
             slotHeight * position.y + defaultTextOffsetY,
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
