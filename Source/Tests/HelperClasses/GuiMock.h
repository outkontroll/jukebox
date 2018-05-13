#ifndef GUIMOCK_H
#define GUIMOCK_H

#include "IGui.h"
#include "ResourceId.h"
#include "gmock/gmock.h"

struct GuiMock : public jukebox::gui::IGui
{
    MOCK_METHOD1(refreshCredits, void(unsigned int));
    MOCK_METHOD1(showStatusMessage, void(jukebox::ResourceId));
    MOCK_METHOD1(showStatistics, void(const std::string&));
    MOCK_METHOD0(refreshAlbums, void());
    MOCK_METHOD1(setFileSystem, void(jukebox::filesystem::IFileSystem*));
    MOCK_METHOD1(setMusicFolder, void(const std::string &));
    MOCK_METHOD1(setTimeToPlaySong, void(int));
    MOCK_METHOD1(setTimeToSaveInsertedCoins, void(int));
    MOCK_METHOD1(setTimeToPlayAdvertiseMusic, void(int));
    MOCK_METHOD1(startAdvertiseMusicTimer, void(int));
    MOCK_METHOD0(turnOffAdvertiseMusic, void());
    MOCK_METHOD1(setPassword, void(const jukebox::Password*));
    MOCK_METHOD0(turnOffPassword, void());
    MOCK_METHOD1(setCurrentlyPlayedSong, void(const jukebox::audio::Song&));
    MOCK_METHOD1(enqueue, void(const jukebox::audio::Song&));
    MOCK_METHOD0(removeCurrentSong, void());
    MOCK_METHOD0(prepareForExit, void());
};

#endif //GUIMOCK_H
