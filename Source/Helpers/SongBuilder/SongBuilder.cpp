#include "SongBuilder.h"
#include "FileSystem.h"
#include "Formaters.h"

using namespace jukebox::songbuilder;
using namespace jukebox::audio;
using namespace jukebox::filesystem;

Song SongBuilder::buildSong(unsigned int albumNumber, unsigned int songNumber, const std::string& musicDirectory)
{
    return { albumNumber,
             songNumber,
             FileSystem::getSongFilePath(musicDirectory, albumNumber, songNumber, "*.mp3"),
             std::string(FillWithLeadingZeros(albumNumber, 3) + FillWithLeadingZeros(songNumber, 2))
             };
}

std::vector<Song> SongBuilder::buildSongsInAlbum(unsigned int /*albumNumber*/, const std::string& /*musicDirectory*/)
{
    //TODO
    return {};
}
