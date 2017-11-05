#ifndef SONG_H_INCLUDED
#define SONG_H_INCLUDED

#include <tuple>
#include <string>

namespace jukebox { namespace audio {

class Album
{
public:
    explicit Album(unsigned int albumNumber_)
    : albumNumber(albumNumber_)
    {
    }

    inline unsigned int getAlbumNumber() const
    {
        return albumNumber;
    }
private:
    const unsigned int albumNumber;
};

struct Song
{
    inline bool operator<(const Song& other) const
    {
        return std::tie(albumNumber, songNumber, fileName) < std::tie(other.albumNumber, other.songNumber, fileName);
    }

    inline bool operator==(const Song& other) const
    {
        return std::tie(albumNumber, songNumber, fileName) == std::tie(other.albumNumber, other.songNumber, fileName);
    }

    const unsigned int albumNumber;
    const unsigned int songNumber;
    const std::string fileName;
    const std::string visibleName;
};

}}

#endif  // SONG_H_INCLUDED
