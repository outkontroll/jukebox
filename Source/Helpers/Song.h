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
    : album(albumNumber),
      song(songNumber)
    {}
    
    inline unsigned int getAlbum() const
    {
        return album;
    }

    inline unsigned int getSong() const
    {
        return song;
    }
    
    inline bool operator<(const Song& other) const
    {
        return std::tie(album, song) < std::tie(other.album, other.song);
    }
    
private:
    unsigned int album;
    unsigned int song;
};

}}

#endif  // SONG_H_INCLUDED
