#include "SingleAlbumCanvas.h"
#include <numeric>
#include "ResourceId.h"
#include "ResourceString.h"
#include "Formaters.h"
#include "IFileSystem.h"
#include "SingleAlbumPositionCalculator.h"
#include "StdAddons.hpp"
#include "Song.h"

using namespace jukebox::gui;
using namespace jukebox::filesystem;
using namespace jukebox::audio;
using namespace juce;
using namespace std;

namespace {
    const float bigFontSize = 24.0f;
    const float selectionThickness = 4.0f;
}

void SingleAlbumCanvas::paint(Graphics& g)
{
    g.setColour(Colours::black);
    g.drawRect(Rectangle<int>{0, 0, getWidth(), getHeight()});

    g.setFont(bigFontSize);

    // album's number
    g.drawText(jukebox::FillWithLeadingZeros(albumIndex + 1, 3), albumTextPlace, Justification::centredLeft);

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

void SingleAlbumCanvas::loadAlbum(const std::vector<jukebox::audio::AlbumInfo>& albums, unsigned int selectedAlbumIndex)
{
    artistName = "";
    image = Image{};
    selectionBounds.clear();
    drawableSongNames = "";

    if(albums.empty())
        return;

    albumIndex = selectedAlbumIndex - 1;
    currentSelectedLine = 0;

    const auto& album = albums[albumIndex];
    artistName = album.artist;
    drawableSongNames = std_addons::accumulate(album.songs, juce::String(""), [](const juce::String& lines, const Song& song){
       return lines + song.visibleName.substr(3) + "\n";
    });
    image = ImageFileFormat::loadFrom(File(album.imagePath));

    selectionBounds = SingleAlbumPositionCalculator(getWidth(), getHeight(), static_cast<float>(getWidth() / 2)).calculateSelectionBounds(album.songs, drawableSongNamesPlace);
}

void SingleAlbumCanvas::setSelection(unsigned int selectedSongIndex)
{
    currentSelectedLine = selectedSongIndex;

    repaint();
}
