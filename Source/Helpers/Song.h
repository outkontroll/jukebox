/*
  ==============================================================================

    Song.h
    Created: 12 Apr 2015 2:46:55pm
    Author:  bakos

  ==============================================================================
*/

#ifndef SONG_H_INCLUDED
#define SONG_H_INCLUDED

namespace jukebox { namespace audio {
    
class Song
{
public:
    Song(unsigned int albumNumber = 0, unsigned int songNumber = 0)
    : album(albumNumber),
      song(songNumber)
    {}
    
    unsigned int getAlbum() const
    {
        return album;
    }

    unsigned int getSong() const
    {
        return song;
    }
    
private:
    unsigned int album;
    unsigned int song;
};

struct CompareSong
{
    bool operator()(const Song& lhs, const Song& rhs)
    {
        if(lhs.getAlbum() < rhs.getAlbum())
            return true;
        if(lhs.getAlbum() > rhs.getAlbum())
            return false;
        
        return lhs.getSong() < rhs.getSong();
    }
};

}}

#endif  // SONG_H_INCLUDED
