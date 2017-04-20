#ifndef IMUSICPLAYER_H_INCLUDED
#define IMUSICPLAYER_H_INCLUDED

#include <string>

namespace jukebox { namespace audio {
    
class IMusicPlayer
{
public:
    virtual ~IMusicPlayer() = default;
    
    virtual void playSong(const std::string& song) = 0;

    virtual void stopPlaying() = 0;
};    

}}

#endif  // IMUSICPLAYER_H_INCLUDED
