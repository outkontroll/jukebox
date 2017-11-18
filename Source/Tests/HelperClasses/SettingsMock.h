#ifndef SETTINGSMOCK_H
#define SETTINGSMOCK_H

#include "ISettings.h"

struct SettingsMock : public jukebox::settings::ISettings
{

    // ISettings interface
public:
    std::string getMusicDirectory() const override
    {
        return "FakeMusicDirectory";
    }
};

#endif // SETTINGSMOCK_H
