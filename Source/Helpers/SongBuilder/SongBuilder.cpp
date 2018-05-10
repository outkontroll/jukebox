#include "SongBuilder.h"
#include <algorithm>
#include "JuceHeader.h"
#include "IFileSystem.h"
#include "Formaters.h"

using namespace jukebox::songbuilder;
using namespace jukebox::audio;
using namespace jukebox::filesystem;

namespace {
    const auto DefaultExtensionPattern = "*.mp3";
}

Album SongBuilder::buildAlbum(unsigned int albumNumber)
{
    return { albumNumber,
             createVisibleName(albumNumber)
             };
}

Song SongBuilder::buildSong(unsigned int albumNumber, unsigned int songNumber, const juce::File& file, std::string_view name)
{
    return { albumNumber,
             songNumber,
             file.getFullPathName().toStdString(),
             name.empty() ? file.getFileNameWithoutExtension().toStdString() : std::string(name)
    };
}

std::string SongBuilder::createVisibleName(unsigned int albumNumber, unsigned int songNumber)
{
    return {FillWithLeadingZeros(albumNumber, 3) + FillWithLeadingZeros(songNumber, 2)};
}

std::string SongBuilder::createVisibleName(unsigned int albumNumber)
{
    return FillWithLeadingZeros(albumNumber, 3);
}
