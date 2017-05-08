#include "Settings.h"
#include "Logger.h"

namespace {
    const std::string DefaultMusicDirectory = "/home/adam/Music/test_data/music";
}

using namespace jukebox::settings;

std::string Settings::getMusicDirectory()
{
    return DefaultMusicDirectory;
}
