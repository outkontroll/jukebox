#ifndef ISETTINGS_H_INCLUDED
#define ISETTINGS_H_INCLUDED

#include <string>

namespace jukebox { namespace settings {

class ISettings
{
public:
    virtual ~ISettings() = default;

    virtual std::string getMusicDirectory() const = 0;
    virtual void setMusicDirectory(const std::string& newMusicDirectory) = 0;
};

}}

#endif //ISETTINGS_H_INCLUDED
