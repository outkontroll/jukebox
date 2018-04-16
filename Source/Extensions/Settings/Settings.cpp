#include "Settings.h"
#include "Logger.h"

using namespace jukebox::settings;

Settings::Settings(const std::string& musicDir)
:   musicDirectory(musicDir)
{
}

std::string Settings::getMusicDirectory() const
{
    return musicDirectory;
}

void Settings::setMusicDirectory(const std::string& newMusicDirectory)
{
    musicDirectory = newMusicDirectory;
}
