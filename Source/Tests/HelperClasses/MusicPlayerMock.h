#ifndef MUSICPLAYERMOCK_H
#define MUSICPLAYERMOCK_H

#include "IMusicPlayer.h"

struct MusicPlayerMock : public jukebox::audio::IMusicPlayer
{

    // IMusicPlayer interface
public:
    void playSong(const std::string&) override
    {
    }
    bool isPlaying() const override
    {
        return false;
    }
    void stopPlaying() override
    {
    }
};

#endif // MUSICPLAYERMOCK_H
