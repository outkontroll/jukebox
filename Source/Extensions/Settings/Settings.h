#ifndef SETTINGS_H
#define SETTINGS_H

#include "ISettings.h"
#include <string>

namespace jukebox { namespace settings {

const std::string DefaultMusicDirectory = "/home/adam/Music/test_data/music";

class Settings : public ISettings
{
public:
    explicit Settings(const std::string& musicDir = DefaultMusicDirectory);
    std::string getMusicDirectory() const override;

private:
    std::string musicDirectory;
};

}}

#endif //SETTINGS_H
