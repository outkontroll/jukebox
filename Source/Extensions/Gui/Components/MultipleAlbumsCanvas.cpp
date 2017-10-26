#include "MultipleAlbumsCanvas.h"
#include "FileSystem.h"

using namespace jukebox::gui;
using namespace juce;

void MultipleAlbumsCanvas::paint(Graphics& g)
{
    //TODO just for testing purposes
    g.drawRect(Rectangle<int>{0, 0, getWidth(), getHeight()});

    const float slotWidth = static_cast<float>(getWidth() / colums);
    const float slotHeight = static_cast<float>(getHeight() / rows);

    int index(0);
    for(const auto& image : images)
    {
        if(image.isValid())
        {
            const auto position = getPositionFromIndex(index);

            g.drawImage(image,
                        calculateImagePlace(position, slotWidth, slotHeight),
                        RectanglePlacement::stretchToFit);
        }

        ++index;
    }
}

void MultipleAlbumsCanvas::loadAlbums(const std::string& musicDirectoy, int firstAlbumIndex)
{
    images.clear();

    for(int albumIndex = firstAlbumIndex; albumIndex < firstAlbumIndex + colums * rows; ++albumIndex)
    {
        auto imagePath = jukebox::filesystem::FileSystem::getPicturePath(musicDirectoy, albumIndex, ".jpg");
        auto image = ImageFileFormat::loadFrom(File(imagePath));

        images.push_back(image);
    }
}

Rectangle<float> MultipleAlbumsCanvas::calculateImagePlace(Position position, float slotWidth, float slotHeight) const
{
    const float imageWidth = slotWidth - 20;
    const float imageHeigth = imageWidth;

    return {slotWidth * position.x + (slotWidth - imageWidth) / 2, slotHeight * position.y + (slotHeight - imageHeigth) / 1.8f, imageWidth, imageHeigth};
}

MultipleAlbumsCanvas::Position MultipleAlbumsCanvas::getPositionFromIndex(int index) const
{
    return { index % colums, index / colums };
}
