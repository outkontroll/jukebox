#ifndef SETTINGS_H
#define SETTINGS_H

#include "ISettings.h"
#include <string>

namespace jukebox { namespace settings {

class Settings : public ISettings
{
public:
    Settings(const std::string& musicDir);
    ~Settings() override = default;

    std::string getMusicDirectory() const override;
    void setMusicDirectory(const std::string& newMusicDirectory) override;

private:
    std::string musicDirectory = "";
};

}}

#endif //SETTINGS_H
