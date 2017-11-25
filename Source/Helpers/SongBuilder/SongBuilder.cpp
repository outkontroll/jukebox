#include "SongBuilder.h"
#include "IFileSystem.h"
#include "Formaters.h"
#include <algorithm>

using namespace jukebox::songbuilder;
using namespace jukebox::audio;
using namespace jukebox::filesystem;

namespace {
    const auto DefaultExtensionPattern = "*.mp3";
}

Song SongBuilder::buildSong(unsigned int albumNumber, unsigned int songNumber, const std::string& musicDirectory, const IFileSystem& filesys)
{
    return { albumNumber,
             songNumber,
             filesys.getSongFilePath(musicDirectory, albumNumber, songNumber, DefaultExtensionPattern),
             std::string(FillWithLeadingZeros(albumNumber, 3) + FillWithLeadingZeros(songNumber, 2))
             };
}

std::vector<Song> SongBuilder::buildSongsInAlbum(unsigned int albumNumber, const std::string& musicDirectory, const IFileSystem& filesys)
{
    const auto paths = filesys.getAllSongFilesWithFullPaths(musicDirectory, albumNumber, DefaultExtensionPattern);
    std::vector<Song> songs;
    songs.reserve(paths.size());

    std::transform(paths.begin(), paths.end(), std::back_inserter(songs), [albumNumber](const auto& path){
        return Song{ albumNumber,
                     static_cast<unsigned int>(path.second),
                     path.first,
                     std::string(FillWithLeadingZeros(albumNumber, 3) + FillWithLeadingZeros(path.second, 2))
                     };
    });

    return songs;
}
