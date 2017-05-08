#ifndef SETTINGS_H
#define SETTINGS_H

#include "ISettings.h"

namespace jukebox { namespace settings {

class Settings : public ISettings
{
public:
    std::string getMusicDirectory() override;
};

}}

#endif //SETTINGS_H
