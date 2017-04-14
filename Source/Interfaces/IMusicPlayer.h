#ifndef IMUSICPLAYER_H_INCLUDED
#define IMUSICPLAYER_H_INCLUDED

#include "Song.h"

namespace jukebox { namespace audio {
    
class IMusicPlayer
{
public:
    virtual ~IMusicPlayer() = default;
    
    virtual void playSong(audio::Song song) = 0;
    virtual void playAlbum(audio::Album album) = 0;
    
    virtual void stopPlaying() = 0;
};    

}}

#endif  // IMUSICPLAYER_H_INCLUDED
