#ifndef RESOUCRESTRING_H
#define RESOUCRESTRING_H

#include <string>

namespace jukebox {
    enum class ResourceId;
}

namespace jukebox { namespace gui {

struct Resources
{
    static std::string getResourceStringFromId(jukebox::ResourceId resourceId);
};

}}

#endif // RESOUCRESTRING_H
