#ifndef SONG_H_INCLUDED
#define SONG_H_INCLUDED

#include <tuple>
#include <string>

namespace jukebox { namespace audio {

struct Album
{
    inline bool operator<(const Album& other) const
    {
        return albumNumber < other.albumNumber;
    }

    inline bool operator==(const Album& other) const
    {
        return albumNumber == other.albumNumber;
    }

    const unsigned int albumNumber;
    const std::string visibleName;
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
