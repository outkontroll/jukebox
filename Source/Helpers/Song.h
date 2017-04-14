#ifndef SONG_H_INCLUDED
#define SONG_H_INCLUDED

#include <tuple>

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
    Song(unsigned int albumNumber, unsigned int songNumber)
    : albumNumber(albumNumber),
      songNumber(songNumber)
    {
    }

    Song(Album album, unsigned int songNumber)
    :   albumNumber(album.getAlbumNumber()),
        songNumber(songNumber)
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

    inline bool operator<(const Song& other) const
    {
        return std::tie(albumNumber, songNumber) < std::tie(other.albumNumber, other.songNumber);
    }

private:
    unsigned int albumNumber;
    unsigned int songNumber;
};

}}

#endif  // SONG_H_INCLUDED
