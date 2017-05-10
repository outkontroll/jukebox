#ifndef ISETTINGS_H_INCLUDED
#define ISETTINGS_H_INCLUDED

#include <string>

namespace jukebox { namespace settings {

class ISettings
{
public:
    virtual ~ISettings() = default;

    virtual std::string getMusicDirectory() = 0;
};

}}

#endif //ISETTINGS_H_INCLUDED