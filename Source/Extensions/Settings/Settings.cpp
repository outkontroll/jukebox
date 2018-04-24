#include "Settings.h"

using namespace jukebox::settings;

Settings::Settings(std::string musicDirectory_)
 : musicDirectory(std::move(musicDirectory_))
{
}

std::string Settings::getMusicDirectory() const
{
    return musicDirectory;
}

void Settings::setMusicDirectory(std::string musicDirectory_)
{
    musicDirectory = std::move(musicDirectory_);
}

int Settings::getTimeToPlaySong() const
{
    return millisecsToPlaySong;
}

void Settings::setTimeToPlaySong(int millisecsToPlaySong_)
{
    millisecsToPlaySong = millisecsToPlaySong_;
}
