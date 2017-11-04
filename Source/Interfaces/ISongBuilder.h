#ifndef ISONGBUILDER_H
#define ISONGBUILDER_H

#include "Song.h"
#include <string>
#include <vector>

namespace jukebox { namespace audio {
    class Song;
}}

namespace jukebox { namespace songbuilder {

class ISongBuilder
{
public:
    virtual ~ISongBuilder() = 0;

    virtual audio::Song buildSong(unsigned int albumNumber, unsigned int songNumber, const std::string& musicDirectory) = 0;
    virtual std::vector<audio::Song> buildSongsInAlbum(unsigned int albumNumber, const std::string& musicDirectory) = 0;
};

}}

#endif // ISONGBUILDER_H
