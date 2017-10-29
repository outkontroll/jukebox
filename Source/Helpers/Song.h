#ifndef SONG_H_INCLUDED
#define SONG_H_INCLUDED

#include <tuple>
#include <string>
//TODO eliminate this from here as soon as there is a cpp involved
#include "Formaters.h"

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
    unsigned int albumNumber;
};

class Song
{
public:
    Song(Album album, unsigned int songNumber_, const std::string& fileName_)
    :   albumNumber(album.getAlbumNumber()),
        songNumber(songNumber_),
        fileName(fileName_),
        visibleName(std::string(FillWithLeadingZeros(albumNumber, 3) + FillWithLeadingZeros(songNumber, 2)))
    {
    }

    inline unsigned int getAlbumNumber() const
    {
        return albumNumber;
    }

    inline unsigned int getSongNumber() const
    {
        return songNumber;
    }

    inline const std::string& getFileName() const
    {
        return fileName;
    }

    inline bool operator<(const Song& other) const
    {
        return std::tie(albumNumber, songNumber) < std::tie(other.albumNumber, other.songNumber);
    }

    inline bool operator==(const Song& other) const
    {
        return std::tie(albumNumber, songNumber) == std::tie(other.albumNumber, other.songNumber);
    }

    inline const std::string& toString() const
    {
        return visibleName;
    }

private:
    unsigned int albumNumber = 0;
    unsigned int songNumber = 0;
    std::string fileName = "";
    std::string visibleName = "";
};

}}

#endif  // SONG_H_INCLUDED
