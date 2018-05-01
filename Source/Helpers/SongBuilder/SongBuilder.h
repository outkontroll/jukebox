#ifndef SONGBUILDER_H
#define SONGBUILDER_H

#include "Song.h"
#include <string>
#include <vector>

namespace jukebox { namespace filesystem {
    class IFileSystem;
}
}

namespace jukebox { namespace songbuilder {

struct SongBuilder
{
public:
    static audio::Album buildAlbum(unsigned int albumNumber);
    static audio::Song buildSong(unsigned int albumNumber, unsigned int songNumber, const std::string& musicDirectory, const jukebox::filesystem::IFileSystem& filesys);
    static std::vector<audio::Song> buildSongsInAlbum(unsigned int albumNumber, const std::string& musicDirectory, const jukebox::filesystem::IFileSystem& filesys);
    static std::string createVisibleName(unsigned int albumNumber, unsigned int songNumber);
    static std::string createVisibleName(unsigned int albumNumber);
};

}}

#endif // SONGBUILDER_H
