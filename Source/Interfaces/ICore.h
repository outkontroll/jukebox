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
    
    virtual void initialize(const std::string& name,
                            std::unique_ptr<gui::IGui> iGui,
                            std::unique_ptr<creditmanager::ICreditManager> iCreditManager,
                            std::unique_ptr<audio::IMusicPlayer> iMusicPlayer,
                            std::unique_ptr<statistics::IStatistics> iStatistics) = 0;
    virtual void uninitialize() = 0;

public:
    jukebox::signals::Signal<> exitRequestedSignal;
};

}}

#endif  // ICORE_H_INCLUDED
