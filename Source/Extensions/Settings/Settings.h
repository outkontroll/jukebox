#ifndef SETTINGS_H
#define SETTINGS_H

#include "ISettings.h"
#include <string>

namespace jukebox { namespace settings {

class Settings : public ISettings
{
public:
    Settings(std::string musicDirectory_);
    ~Settings() override = default;

    std::string getMusicDirectory() const override;
    void setMusicDirectory(std::string musicDirectory) override;
    int getTimeToPlaySong() const override;
    void setTimeToPlaySong(int millisecsToPlaySong) override;

private:
    std::string musicDirectory = "";
    int millisecsToPlaySong = 5000;
};

}}

#endif //SETTINGS_H
