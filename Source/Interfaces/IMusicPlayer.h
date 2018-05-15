#ifndef IMUSICPLAYER_H_INCLUDED
#define IMUSICPLAYER_H_INCLUDED

#include <string>
#include "Signals.hpp"

namespace jukebox { namespace audio {
    
class IMusicPlayer
{
public:
    virtual ~IMusicPlayer() = default;
    
    virtual void playSong(const std::string& song) = 0;
    virtual bool isPlaying() const /*noexcept*/ = 0;
    virtual void stopPlaying() = 0;

public:
    jukebox::signals::Signal<> finishedPlayingSignal;
};    

}}

#endif  // IMUSICPLAYER_H_INCLUDED
