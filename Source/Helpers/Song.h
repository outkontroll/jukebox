#ifndef SONG_H_INCLUDED
#define SONG_H_INCLUDED

#include <tuple>
#include <string>
#include "Formaters.h"

namespace jukebox { namespace audio {

class Album
{
public:
    explicit Album(unsigned int albumNumber)
    : albumNumber(albumNumber)
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
    Song() = default;

    Song(unsigned int albumNumber, unsigned int songNumber)
    :   albumNumber(albumNumber),
        songNumber(songNumber),
        fileName(""),
        visibleName(std::string(FillWithLeadingZeros(albumNumber, 3) + FillWithLeadingZeros(songNumber, 2)))
    {
    }

    Song(Album album, unsigned int songNumber)
    :   albumNumber(album.getAlbumNumber()),
        songNumber(songNumber),
        fileName(""),
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

    inline void setFileName(std::string fn)
    {
        fileName = std::move(fn);
    }

    inline bool operator<(const Song& other) const
    {
        return std::tie(albumNumber, songNumber) < std::tie(other.albumNumber, other.songNumber);
    }

    inline const std::string& toString() const
    {
        return visibleName;
    }

private:
    unsigned int albumNumber;
    unsigned int songNumber;
    std::string fileName;
    std::string visibleName;
};

}}

#endif  // SONG_H_INCLUDED
