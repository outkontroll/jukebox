#ifndef SONGBUILDER_H
#define SONGBUILDER_H

#include "ISongBuilder.h"
#include <string>

namespace jukebox { namespace songbuilder {

class SongBuilder : public ISongBuilder
{
    // ISongBuilder interface
public:
    audio::Song buildSong(unsigned int albumNumber, unsigned int songNumber, const std::string& musicDirectory) override;
    std::vector<audio::Song> buildSongsInAlbum(unsigned int albumNumber, const std::string& musicDirectory) override;
};

}}

#endif // SONGBUILDER_H
