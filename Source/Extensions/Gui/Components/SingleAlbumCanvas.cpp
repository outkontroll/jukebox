#include "SingleAlbumCanvas.h"
#include "ResourceId.h"
#include "ResourceString.h"
#include "Formaters.h"
#include "FileSystem.h"

using namespace jukebox::gui;
using namespace juce;

namespace {
    const float bigFontSize = 24.0f;
    const float defaultTextOffsetX = 10.0f;
    const float defaultTextOffsetY = 10.0f;
    const float offsetXRatio = 0.963f;
}

void SingleAlbumCanvas::paint(Graphics& g)
{
    //TODO just for testing purposes
    g.setColour(Colours::aqua);
    g.drawRect(Rectangle<int>{0, 0, getWidth(), getHeight()});
    g.setColour(Colours::black);
    //END TODO

    auto currentFont = g.getCurrentFont();
    currentFont.setHeight(bigFontSize);
    g.setFont(currentFont);

    const float pictureSize = static_cast<float>(getWidth() / 2);

    // album's number
    const auto textPlace = calculateTextPlace(pictureSize);
    g.drawText(jukebox::FillWithLeadingZeros(albumIndex, 3), textPlace, Justification::centredLeft);

    // album's image, if we can find one
    const auto imagePlace = calculateImagePlace(pictureSize);
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
}

void SingleAlbumCanvas::loadAlbum(const std::string& musicDirectory, int firstAlbumIndex)
{
    albumIndex = firstAlbumIndex;
    auto imagePath = jukebox::filesystem::FileSystem::getPicturePath(musicDirectory, albumIndex, ".jpg");
    image = ImageFileFormat::loadFrom(File(imagePath));
    repaint();
}

Rectangle<float> SingleAlbumCanvas::calculateImagePlace(float imageSize) const
{
    const float xPosition = (getWidth() / 2 - imageSize * offsetXRatio) / 2;
    const float yPosition = (getHeight() - imageSize) / 2;
    return {xPosition, yPosition, imageSize, imageSize};
}

juce::Rectangle<float> SingleAlbumCanvas::calculateTextPlace(float imageSize) const
{
    const float xPosition = (getWidth() / 2 - imageSize * offsetXRatio) / 2 + defaultTextOffsetX;
    const float textHeight = bigFontSize;
    const float textWidth = getWidth();

    return { xPosition, defaultTextOffsetY, textWidth, textHeight};
}
