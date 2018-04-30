#include "SingleAlbumCanvas.h"
#include <numeric>
#include "ResourceId.h"
#include "ResourceString.h"
#include "Formaters.h"
#include "IFileSystem.h"
#include "SingleAlbumPositionCalculator.h"

using namespace jukebox::gui;
using namespace jukebox::filesystem;
using namespace juce;
using namespace std;

namespace {
    const float bigFontSize = 24.0f;
    //const float defaultTextOffsetX = 10.0f;
    //const float defaultTextOffsetY = 10.0f;
    //const float offsetXRatio = 0.963f;
    const float selectionThickness = 4.0f;
    //const float offsetX = 4.0f;
    //const float offsetY = 3.0f;
    const char* defaultImageExtension = ".jpg";
    const char* defaultMusicExtension = "*.mp3";
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
    g.drawText(jukebox::FillWithLeadingZeros(albumIndex, 3), albumTextPlace, Justification::centredLeft);

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

    if(!drawableSongNames.isEmpty())
    {
        g.setColour(Colours::yellow);
        g.drawRect(selectionBounds[currentSelectedLine], selectionThickness);
        g.setColour(Colours::black);

        g.drawMultiLineText(drawableSongNames, drawableSongNamesPlace[0], drawableSongNamesPlace[1], drawableSongNamesPlace[2]);
    }
}

void SingleAlbumCanvas::parentSizeChanged()
{
    const float width = getWidth();
    const float height = getHeight();
    const float pictureSize = static_cast<float>(width / 2);

    SingleAlbumPositionCalculator positions(width, height, pictureSize);

    albumTextPlace = positions.calculateAlbumTextPlace();
    imagePlace = positions.calculateImagePlace();
    artistNamePlace = positions.calculateArtistTextPlace();
    drawableSongNamesPlace = positions.calculateDrawableSongNamesPlace();
}

void SingleAlbumCanvas::loadAlbum(const std::string& musicDirectory, unsigned int selectedAlbumIndex, const jukebox::filesystem::IFileSystem& fileSys)
{
    albumIndex = selectedAlbumIndex;
    currentSelectedLine = 0;
    loadImage(musicDirectory, fileSys);
    std::tie(artistName, drawableSongNames, songNames) = loadInfoFile(musicDirectory, fileSys, albumIndex);

    if(!songNames.empty())
        selectionBounds = SingleAlbumPositionCalculator(getWidth(), getHeight(), static_cast<float>(getWidth() / 2)).calculateSelectionBounds(songNames, drawableSongNamesPlace);

    repaint();
}

void SingleAlbumCanvas::setSelection(unsigned int selectedSongIndex)
{
    currentSelectedLine = selectedSongIndex;

    if(!songNames.empty())
        selectionBounds = SingleAlbumPositionCalculator(getWidth(), getHeight(), static_cast<float>(getWidth() / 2)).calculateSelectionBounds(songNames, drawableSongNamesPlace);

    repaint();
}

void SingleAlbumCanvas::loadImage(const std::string& musicDirectory, const filesystem::IFileSystem& fileSys)
{
    auto imagePath = fileSys.getPicturePath(musicDirectory, albumIndex, defaultImageExtension);
    image = ImageFileFormat::loadFrom(File(imagePath));
}

inline auto readMusicFiles(const std::string& musicDirectory, const IFileSystem& fileSys, unsigned int albumIndex)
{
    auto musicFiles = fileSys.getAllSongFilesNamesOnly(musicDirectory, albumIndex, defaultMusicExtension);
    String drawableSongNames = std::accumulate(musicFiles.begin(), musicFiles.end(), juce::String(""), [](const juce::String& current, const std::string& line){
       return current + line + '\n';
    });

    vector<String> songNames;
    songNames.reserve(musicFiles.size());
    std::transform(musicFiles.begin(), musicFiles.end(), std::back_inserter(songNames), [](const std::string& line){
       return line;
    });

    return std::make_tuple(drawableSongNames, songNames);
}

auto SingleAlbumCanvas::loadInfoFile(const std::string& musicDirectory, const filesystem::IFileSystem& fileSys, unsigned int albumIndex_) const ->
std::tuple<juce::String, juce::String, std::vector<juce::String>>
{
    juce::String artistName_ = Resources::getResourceStringFromId(ResourceId::DefaultArtistName);

    auto infoFilePath = fileSys.getInfoFilePath(musicDirectory, albumIndex_);
    File infoFile(infoFilePath);

    if(!infoFile.existsAsFile())
    {
        const auto [drawableSongNames_, songNames_] = readMusicFiles(musicDirectory, fileSys, albumIndex_);
        return std::make_tuple(artistName_, drawableSongNames_, songNames_);
    }

    juce::String drawableSongNames_ = "";
    std::vector<juce::String> songNames_;

    StringArray lines;
    infoFile.readLines(lines);

    std::remove_if(lines.begin(), lines.end(), [](const String& current){
       return current.isEmpty();
    });

    if(lines.size() > 0)
    {
        if(lines[0].isNotEmpty())
        {
            artistName_ = lines[0];
            lines.remove(0);
        }

        drawableSongNames_ = std::accumulate(lines.begin(), lines.end(), String(""), [](const String& current, const String& line){
           return current + line + '\n';
        });

        std::transform(lines.begin(), lines.end(), back_inserter(songNames_), [](const String& current){
            return current;
        });
    }

    if(drawableSongNames_.isEmpty())
    {
        tie(drawableSongNames_, songNames_) = readMusicFiles(musicDirectory, fileSys, albumIndex_);
    }

    return std::make_tuple(artistName_, drawableSongNames_, songNames_);
}
