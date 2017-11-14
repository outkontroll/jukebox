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
    const std::string defaultImageExtension = ".jpg";
    const std::string defaultMusicExtension = "*.mp3";
}

void SingleAlbumCanvas::paint(Graphics& g)
{
    //TODO just for testing purposes
    g.setColour(Colours::aqua);
    g.drawRect(Rectangle<int>{0, 0, getWidth(), getHeight()});
    //END TODO

    g.setColour(Colours::black);

    auto currentFont = g.getCurrentFont();
    currentFont.setHeight(bigFontSize);
    g.setFont(currentFont);

    const float width = getWidth();
    const float height = getHeight();
    const float pictureSize = static_cast<float>(width / 2);

    // album's number
    const auto textPlace = calculateTextPlace(pictureSize, width);
    g.drawText(jukebox::FillWithLeadingZeros(albumIndex, 3), textPlace, Justification::centredLeft);

    // album's image, if we can find one
    const auto imagePlace = calculateImagePlace(pictureSize, width, height);
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

    // album's contain, if there is one
    if(!artistName.isEmpty())
    {
        const auto artistNamePlace = calculateArtistTextPlace(pictureSize, width);
        g.drawText(artistName, artistNamePlace, Justification::centred);
    }

    if(!otherLines.isEmpty())
    {
        const auto otherLinesPlace = calculateOtherLinesPlace(pictureSize, width, height);
        g.drawMultiLineText(otherLines, otherLinesPlace.startX, otherLinesPlace.baselineY, otherLinesPlace.maximumLineWidth);
    }
}

void SingleAlbumCanvas::loadAlbum(const std::string& musicDirectory, int selectedAlbumIndex)
{
    albumIndex = selectedAlbumIndex;
    loadImage(musicDirectory);
    loadInfoFile(musicDirectory);

    repaint();
}

void SingleAlbumCanvas::loadImage(const std::string& musicDirectory)
{
    auto imagePath = jukebox::filesystem::FileSystem::getPicturePath(musicDirectory, albumIndex, defaultImageExtension);
    image = ImageFileFormat::loadFrom(File(imagePath));
}

void SingleAlbumCanvas::loadInfoFile(const std::string& musicDirectory)
{
    otherLines = "";
    artistName = "";

    StringArray lines;
    auto infoFilePath = jukebox::filesystem::FileSystem::getInfoFilePath(musicDirectory, albumIndex);
    File infoFile(infoFilePath);
    if(!infoFile.existsAsFile())
    {
        lines.add(Resources::getResourceStringFromId(ResourceId::DefaultArtistName));

        auto musicFiles = jukebox::filesystem::FileSystem::getAllSongFilesNamesOnly(musicDirectory, albumIndex, defaultMusicExtension);
        for(auto& musicFile : musicFiles)
        {
            lines.add(musicFile);
        }
    }
    else
    {
        infoFile.readLines(lines);
    }

    if(lines.size() == 0)
    {
        return;
    }

    artistName = lines[0];

    otherLines = std::accumulate(std::next(lines.begin()), lines.end(), juce::String(""), [](const juce::String& current, const juce::String& line){
       return line.isEmpty() ? current : current + line + '\n';
    });
}

Rectangle<float> SingleAlbumCanvas::calculateImagePlace(float imageSize, float width, float height) const
{
    const float xPosition = (width / 2 - imageSize * offsetXRatio) / 2;
    const float yPosition = (height - imageSize) / 2;
    return { xPosition, yPosition, imageSize, imageSize };
}

juce::Rectangle<float> SingleAlbumCanvas::calculateTextPlace(float imageSize, float width) const
{
    const float xPosition = (width / 2 - imageSize * offsetXRatio) / 2 + defaultTextOffsetX;
    const float textHeight = bigFontSize;
    const float textWidth = width;

    return { xPosition, defaultTextOffsetY, textWidth, textHeight };
}

juce::Rectangle<float> SingleAlbumCanvas::calculateArtistTextPlace(float imageSize, float width) const
{
    const float xPosition = (width / 2 - imageSize * offsetXRatio) / 2 + defaultTextOffsetX + imageSize;
    const float textHeight = bigFontSize;
    const float textWidth = width / 2;

    return { xPosition, defaultTextOffsetX, textWidth, textHeight };
}

SingleAlbumCanvas::MultipleLinesPosition SingleAlbumCanvas::calculateOtherLinesPlace(float imageSize, float width, float height) const
{
    const int startX = (width / 2 - imageSize * offsetXRatio) / 2 + defaultTextOffsetX + imageSize;
    const int baseLineY = (height - imageSize) / 2;
    const int maximumLineWidth = width - startX - defaultTextOffsetX;

    return { startX, baseLineY, maximumLineWidth };
}
