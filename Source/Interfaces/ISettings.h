#ifndef ISETTINGS_H_INCLUDED
#define ISETTINGS_H_INCLUDED

#include <string>

namespace jukebox { namespace settings {

class ISettings
{
public:
    virtual ~ISettings() = default;

    virtual std::string getMusicDirectory() const = 0;
    virtual void setMusicDirectory(std::string musicDirectory) = 0;
    virtual int getTimeToPlaySong() const = 0;
    virtual void setTimeToPlaySong(int millisecs) = 0;
};

}}

#endif //ISETTINGS_H_INCLUDED
