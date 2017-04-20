#ifndef MUSICPLAYER_H_INCLUDED
#define MUSICPLAYER_H_INCLUDED

#include <memory>
#include "IMusicPlayer.h"

namespace jukebox { namespace audio {
  
class MusicPlayer : public IMusicPlayer
{
public:
    MusicPlayer();

    void playSong(const std::string&) override;

    void stopPlaying() override;
    
private:
    std::unique_ptr<IMusicPlayer> pImpl;
};

}}
    
#endif  // MUSICPLAYER_H_INCLUDED
