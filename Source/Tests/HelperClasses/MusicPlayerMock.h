#ifndef MUSICPLAYERMOCK_H
#define MUSICPLAYERMOCK_H

#include "IMusicPlayer.h"
#include "gmock/gmock.h"

struct MusicPlayerMock : public jukebox::audio::IMusicPlayer
{
    // IMusicPlayer interface
public:
    MOCK_METHOD1(playSong, void(const std::string&));
    MOCK_CONST_METHOD0(isPlaying, bool());
    MOCK_METHOD0(stopPlaying, void());
};

#endif // MUSICPLAYERMOCK_H
