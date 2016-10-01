/*
  ==============================================================================

    ICore.h
    Created: 14 Mar 2015 3:27:52am
    Author:  adam

  ==============================================================================
*/

#ifndef ICORE_H_INCLUDED
#define ICORE_H_INCLUDED

#include <string>
#include "Signals.hpp"

namespace std
{
    template<class T> class shared_ptr;
}

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
    virtual ~ICore(){}
    
    virtual void initialize(const std::string& name,
                            const std::shared_ptr<gui::IGui>& iGui,
                            const std::shared_ptr<creditmanager::ICreditManager>& iCreditManager,
                            const std::shared_ptr<audio::IMusicPlayer>& iMusicPlayer,
                            const std::shared_ptr<statistics::IStatistics>& iStatistics) = 0;
    virtual void uninitialize() = 0;

public:
    jukebox::signals::Signal<> exitRequestedSignal;
};

}}

#endif  // ICORE_H_INCLUDED
