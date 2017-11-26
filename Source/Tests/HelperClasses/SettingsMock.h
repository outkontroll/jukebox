#ifndef SETTINGSMOCK_H
#define SETTINGSMOCK_H

#include "ISettings.h"
#include "gmock/gmock.h"

struct SettingsMock : public jukebox::settings::ISettings
{

    // ISettings interface
public:
    MOCK_CONST_METHOD0(getMusicDirectory, std::string());
    MOCK_METHOD1(setMusicDirectory, void(std::string));
    MOCK_CONST_METHOD0(getTimeToPlaySong, int());
    MOCK_METHOD1(setTimeToPlaySong, void(int));
};

#endif // SETTINGSMOCK_H
