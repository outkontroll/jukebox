#ifndef SONGBUILDER_H
#define SONGBUILDER_H

#include "Song.h"
#include <string>
#include <vector>

namespace jukebox { namespace songbuilder {

class SongBuilder
{
public:
    static audio::Song buildSong(unsigned int albumNumber, unsigned int songNumber, const std::string& musicDirectory);
    static std::vector<audio::Song> buildSongsInAlbum(unsigned int albumNumber, const std::string& musicDirectory);
};

}}

#endif // SONGBUILDER_H
