#ifndef GUIMOCK_H
#define GUIMOCK_H

#include "IGui.h"

struct GuiMock : public jukebox::gui::IGui
{
    // IGui interface
    void refreshCredits(unsigned int) override {}
    void showStatusMessage(const std::string &) override {}
    void setMusicFolder(const std::string &) override {}
    void enqueue(const jukebox::audio::Song&) override {}
    void removeCurrentSong() override {}
};

#endif //GUIMOCK_H
