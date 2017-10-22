#ifndef GUIMOCK_H
#define GUIMOCK_H

#include "IGui.h"
#include "ResourceId.h"
#include "gmock/gmock.h"

struct GuiMock : public jukebox::gui::IGui
{
    MOCK_METHOD1(refreshCredits, void(unsigned int));
    MOCK_METHOD1(showStatusMessage, void(jukebox::ResourceId));
    MOCK_METHOD1(setMusicFolder, void(const std::string &));
    MOCK_METHOD1(setCurrentlyPlayedSong, void(const jukebox::audio::Song&));
    MOCK_METHOD1(enqueue, void(const jukebox::audio::Song&));
    MOCK_METHOD0(removeCurrentSong, void());
};

#endif //GUIMOCK_H
