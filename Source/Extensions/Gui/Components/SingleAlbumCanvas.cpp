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
    const float selectionThickness = 4.0f;
    const float offsetX = 4.0f;
    const float offsetY = 3.0f;
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

    // album's number
    g.drawText(jukebox::FillWithLeadingZeros(albumIndex, 3), textPlace, Justification::centredLeft);

    // album's image, if we can find one
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
        g.drawText(artistName, artistNamePlace, Justification::centred);
    }

    if(!otherLines.isEmpty())
    {
        g.setColour(Colours::yellow);
        g.drawRect(selectionBounds, selectionThickness);
        g.setColour(Colours::black);

        g.drawMultiLineText(otherLines, otherLinesPlace.startX, otherLinesPlace.baselineY, otherLinesPlace.maximumLineWidth);
    }
}

void SingleAlbumCanvas::parentSizeChanged()
{
    const float width = getWidth();
    const float height = getHeight();
    const float pictureSize = static_cast<float>(width / 2);
    textPlace = calculateTextPlace(pictureSize, width);
    imagePlace = calculateImagePlace(pictureSize, width, height);
    artistNamePlace = calculateArtistTextPlace(pictureSize, width);
    otherLinesPlace = calculateOtherLinesPlace(pictureSize, width, height);
}

void SingleAlbumCanvas::loadAlbum(const std::string& musicDirectory, int selectedAlbumIndex)
{
    albumIndex = selectedAlbumIndex;
    currentSelectedLine = 0;
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
    artistName = Resources::getResourceStringFromId(ResourceId::DefaultArtistName);
    songNames.clear();

    auto readMusicFiles = [&]() mutable {
        auto musicFiles = jukebox::filesystem::FileSystem::getAllSongFilesNamesOnly(musicDirectory, albumIndex, defaultMusicExtension);
        otherLines = std::accumulate(musicFiles.begin(), musicFiles.end(), juce::String(""), [](const juce::String& current, const std::string& line){
           return current + line + '\n';
        });

        std::transform(musicFiles.begin(), musicFiles.end(), std::back_inserter(songNames), [](const std::string& line){
           return line;
        });
    };

    auto infoFilePath = jukebox::filesystem::FileSystem::getInfoFilePath(musicDirectory, albumIndex);
    File infoFile(infoFilePath);

    if(!infoFile.existsAsFile())
    {
        readMusicFiles();
    }
    else
    {
        StringArray lines;
        infoFile.readLines(lines);

        std::remove_if(lines.begin(), lines.end(), [](const juce::String& current){
           return current.isEmpty();
        });

        if(lines.size() > 0)
        {
            if(lines[0].isNotEmpty())
            {
                artistName = lines[0];
                lines.remove(0);
            }

            otherLines = std::accumulate(lines.begin(), lines.end(), juce::String(""), [](const juce::String& current, const juce::String& line){
               return current + line + '\n';
            });

            std::transform(lines.begin(), lines.end(), std::back_inserter(songNames), [](const juce::String& current){
                return current;
            });
        }

        if(otherLines.isEmpty())
        {
            readMusicFiles();
        }
    }

    if(!songNames.empty())
        selectionBounds = calculateSelectionBounds(songNames, otherLinesPlace);
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

juce::Rectangle<float> SingleAlbumCanvas::calculateSelectionBounds(const std::vector<String>& lines, MultipleLinesPosition position)
{
    //TODO
    //assert(currentSelectedLine < lines.size());

    const juce::Font font(bigFontSize);
    std::vector<int> lineCounts(currentSelectedLine + 1);

    std::transform(lineCounts.begin(), lineCounts.end(), lines.begin(), lineCounts.begin(), [&](int, const String& line){
        return (font.getStringWidth(line) / position.maximumLineWidth) + 1;
    });

    GlyphArrangement glyphArrangement;
    glyphArrangement.addJustifiedText (font,
                                       "0",
                                       static_cast<float>(position.startX),
                                       static_cast<float>(position.baselineY),
                                       static_cast<float>(position.maximumLineWidth),
                                       Justification::left);

    const auto topOfSelectedLine = std::accumulate(lineCounts.begin(),
                                                   lineCounts.end() - 1,
                                                   glyphArrangement.getGlyph(0).getBounds().getTopLeft().getY(),
                                                   [&](float currentHeight, int lineCount){
        return currentHeight + lineCount * bigFontSize;
    });

    const Point<float> selectionTopLeft = {static_cast<float>(position.startX) - offsetX,
                                           topOfSelectedLine - offsetY};
    const Point<float> selectionBottomRight = {static_cast<float>(position.startX) + position.maximumLineWidth + offsetX,
                                               topOfSelectedLine + lineCounts[currentSelectedLine] * bigFontSize + offsetY};

    return {selectionTopLeft, selectionBottomRight};
}
