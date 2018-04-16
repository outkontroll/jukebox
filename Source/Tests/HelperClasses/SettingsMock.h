#ifndef SETTINGSMOCK_H
#define SETTINGSMOCK_H

#include "ISettings.h"
#include "gmock/gmock.h"

struct SettingsMock : public jukebox::settings::ISettings
{
    MOCK_CONST_METHOD0(getMusicDirectory, std::string());
    MOCK_METHOD1(setMusicDirectory, void(const std::string&));
};

#endif // SETTINGSMOCK_H
