#include "SongBuilder.h"
#include <algorithm>
#include "JuceHeader.h"
#include "IFileSystem.h"
#include "Formaters.h"

using namespace jukebox::songbuilder;
using namespace jukebox::audio;
using namespace jukebox::filesystem;

Album SongBuilder::buildAlbum(int albumNumber)
{
    return { albumNumber,
             createVisibleName(albumNumber)
             };
}

Song SongBuilder::buildSong(int albumNumber, int songNumber, const juce::File& file, std::string_view name)
{
    return { albumNumber,
             songNumber,
             file.getFullPathName().toStdString(),
             createVisibleName(albumNumber, songNumber) + (name.empty() ? file.getFileNameWithoutExtension().toStdString() : std::string(name)).substr(2)
    };
}

std::string SongBuilder::createVisibleName(int albumNumber, int songNumber)
{
    return {FillWithLeadingZeros(albumNumber, 3) + FillWithLeadingZeros(songNumber, 2)};
}

std::string SongBuilder::createVisibleName(int albumNumber)
{
    return FillWithLeadingZeros(albumNumber, 3);
}
