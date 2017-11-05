#include "SongBuilder.h"
#include "FileSystem.h"
#include "Formaters.h"
#include <algorithm>

using namespace jukebox::songbuilder;
using namespace jukebox::audio;
using namespace jukebox::filesystem;

namespace {
    const auto DefaultExtensionPattern = "*.mp3";
}

Song SongBuilder::buildSong(unsigned int albumNumber, unsigned int songNumber, const std::string& musicDirectory)
{
    return { albumNumber,
             songNumber,
             FileSystem::getSongFilePath(musicDirectory, albumNumber, songNumber, DefaultExtensionPattern),
             std::string(FillWithLeadingZeros(albumNumber, 3) + FillWithLeadingZeros(songNumber, 2))
             };
}

std::vector<Song> SongBuilder::buildSongsInAlbum(unsigned int albumNumber, const std::string& musicDirectory)
{
    const auto paths = FileSystem::getAllSongFilePaths(musicDirectory, albumNumber, DefaultExtensionPattern);
    std::vector<Song> songs;
    songs.reserve(paths.size());

    std::for_each(paths.begin(), paths.end(), [&songs, albumNumber](const auto& path){
        songs.emplace_back(Song{ albumNumber,
                                 static_cast<unsigned int>(path.second),
                                 path.first,
                                 std::string(FillWithLeadingZeros(albumNumber, 3) + FillWithLeadingZeros(path.second, 2))
                                 });
    });

    return songs;
}
