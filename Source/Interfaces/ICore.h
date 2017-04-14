#ifndef ICORE_H_INCLUDED
#define ICORE_H_INCLUDED

#include <string>
#include <memory>
#include "Signals.hpp"

namespace jukebox 
{
    namespace gui
    {
        class IGui;
    }
    namespace creditmanager
    {
        class ICreditManager;
    }
    namespace audio
    {
        class IMusicPlayer;
    }
    namespace statistics
    {
        class IStatistics;
    }
}

namespace jukebox { namespace core {

class ICore
{
public:
    virtual ~ICore() = default;

    jukebox::signals::Signal<> exitRequestedSignal;
};

}}

#endif  // ICORE_H_INCLUDED
