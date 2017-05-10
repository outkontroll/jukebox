#include "Settings.h"
#include "Logger.h"

using namespace jukebox::settings;

Settings::Settings(const std::string& musicDir)
:   musicDirectory(musicDir)
{
}

std::string Settings::getMusicDirectory()
{
    return musicDirectory;
}
