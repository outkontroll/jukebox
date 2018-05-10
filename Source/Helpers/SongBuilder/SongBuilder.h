#ifndef SONGBUILDER_H
#define SONGBUILDER_H

#include <string>
#include <string_view>
#include <vector>
#include "Song.h"

namespace juce {
    class File;
}

namespace jukebox { namespace filesystem {
    class IFileSystem;
}
}

namespace jukebox { namespace songbuilder {

struct SongBuilder
{
public:
    static audio::Album buildAlbum(unsigned int albumNumber);
    static audio::Song buildSong(unsigned int albumNumber, unsigned int songNumber, const juce::File& file, std::string_view name);
    static std::string createVisibleName(unsigned int albumNumber, unsigned int songNumber);
    static std::string createVisibleName(unsigned int albumNumber);
};

}}

#endif // SONGBUILDER_H
