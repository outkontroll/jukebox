#include "MultipleAlbumsCanvas.h"
#include "FileSystem.h"
#include "Formaters.h"
#include "ResourceId.h"
#include "ResourceString.h"

using namespace jukebox::gui;
using namespace juce;

namespace {
    const float bigFontSize = 24.0f;
    const float defaultImageOffsetX = 20.0f;
    const float defaultTextOffsetX = 10.0f;
    const float defaultTextOffsetY = 10.0f;
    const float imageOffsetYMultiplier = 1.8f;
}

void MultipleAlbumsCanvas::paint(Graphics& g)
{
    //TODO just for testing purposes
    g.drawRect(Rectangle<int>{0, 0, getWidth(), getHeight()});

    const float slotWidth = static_cast<float>(getWidth() / colums);
    const float slotHeight = static_cast<float>(getHeight() / rows);

    auto currentFont = g.getCurrentFont();
    currentFont.setHeight(bigFontSize);
    g.setFont(currentFont);

    int index(0);
    for(const auto& album : albums)
    {
        const auto& image = album.first;
        const auto position = getPositionFromIndex(index);

        // album's number
        const auto textPlace = calculateTextPlace(position, slotWidth, slotHeight);
        g.drawText(jukebox::FillWithLeadingZeros(album.second, 3), textPlace, Justification::centredLeft);

        // album's image, if we can find one
        const auto imagePlace = calculateImagePlace(position, slotWidth, slotHeight);
        if(image.isValid())
        {
            g.drawImage(image,
                        imagePlace,
                        RectanglePlacement::stretchToFit);
        }
        else
        {
            g.drawText(Resources::getResourceStringFromId(ResourceId::ErrorImageNotFound), imagePlace, Justification::centred );
        }

        ++index;
    }
}

void MultipleAlbumsCanvas::loadAlbums(const std::string& musicDirectoy, int firstAlbumIndex)
{
    albums.clear();

    for(int albumIndex = firstAlbumIndex; albumIndex < firstAlbumIndex + colums * rows; ++albumIndex)
    {
        auto imagePath = jukebox::filesystem::FileSystem::getPicturePath(musicDirectoy, albumIndex, ".jpg");
        auto image = ImageFileFormat::loadFrom(File(imagePath));

        albums.push_back({image, albumIndex});
    }
}

Rectangle<float> MultipleAlbumsCanvas::calculateImagePlace(Position position, float slotWidth, float slotHeight) const
{
    const float imageWidth = slotWidth - defaultImageOffsetX;
    const float imageHeigth = imageWidth;

    return {slotWidth * position.x + (slotWidth - imageWidth) / 2, slotHeight * position.y + (slotHeight - imageHeigth) / imageOffsetYMultiplier, imageWidth, imageHeigth};
}

juce::Rectangle<float> MultipleAlbumsCanvas::calculateTextPlace(MultipleAlbumsCanvas::Position position, float slotWidth, float slotHeight) const
{
    const float textHeight = bigFontSize;
    const float textWidth = slotWidth;
    const float imageWidth = slotWidth - defaultImageOffsetX;

    return {slotWidth * position.x + (slotWidth - imageWidth) / 2 + defaultTextOffsetX, slotHeight * position.y + defaultTextOffsetY, textWidth, textHeight};
}

MultipleAlbumsCanvas::Position MultipleAlbumsCanvas::getPositionFromIndex(int index) const
{
    return { index % colums, index / colums };
}
