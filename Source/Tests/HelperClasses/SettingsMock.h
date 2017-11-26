#ifndef SETTINGSMOCK_H
#define SETTINGSMOCK_H

#include "ISettings.h"
#include "gmock/gmock.h"

struct SettingsMock : public jukebox::settings::ISettings
{

    // ISettings interface
public:
    std::string getMusicDirectory() const override
    {
        return "FakeMusicDirectory";
    }

    MOCK_CONST_METHOD0(getTimeToPlaySong, int());
    MOCK_METHOD1(setTimeToPlaySong, void(int));
};

#endif // SETTINGSMOCK_H
