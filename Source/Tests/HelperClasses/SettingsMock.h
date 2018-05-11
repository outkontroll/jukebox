#ifndef SETTINGSMOCK_H
#define SETTINGSMOCK_H

#include "ISettings.h"
#include "gmock/gmock.h"
#include "Password.h"

struct SettingsMock : public jukebox::settings::ISettings
{
    MOCK_CONST_METHOD0(getMusicDirectory, std::string());
    MOCK_METHOD1(setMusicDirectory, void(std::string));
    MOCK_CONST_METHOD0(getTimeToPlaySong, int());
    MOCK_METHOD1(setTimeToPlaySong, void(int));
    MOCK_CONST_METHOD0(getTimeToSaveInsertedCoins, int());
    MOCK_METHOD1(setTimeToSaveInsertedCoins, void(int));
    MOCK_CONST_METHOD0(isPasswordSet, bool());
    MOCK_METHOD0(turnOffPassword, void());
    MOCK_CONST_METHOD0(getPassword, const jukebox::Password*());
    MOCK_METHOD1(setPassword, void(const jukebox::Password&));
};

#endif // SETTINGSMOCK_H
