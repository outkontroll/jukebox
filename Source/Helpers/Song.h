/*
  ==============================================================================

    Song.h
    Created: 12 Apr 2015 2:46:55pm
    Author:  bakos

  ==============================================================================
*/

#ifndef SONG_H_INCLUDED
#define SONG_H_INCLUDED

#include <tuple>

namespace jukebox { namespace audio {
    
class Song
{
public:
    Song(unsigned int albumNumber = 0, unsigned int songNumber = 0)
    : albumNumber(albumNumber),
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
