/*
  ==============================================================================

    IMusicPlayer.h
    Created: 12 Apr 2015 3:11:52pm
    Author:  bakos

  ==============================================================================
*/

#ifndef IMUSICPLAYER_H_INCLUDED
#define IMUSICPLAYER_H_INCLUDED

#include "Song.h"

namespace jukebox { namespace audio {
    
class IMusicPlayer
{
public:
    virtual ~IMusicPlayer(){}
    
    virtual void playSong(audio::Song song) = 0;
    virtual void playAlbum(audio::Song album) = 0;
    
    virtual void stopPlaying() = 0;
};    

}}

#endif  // IMUSICPLAYER_H_INCLUDED
