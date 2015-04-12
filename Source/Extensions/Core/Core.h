/*
  ==============================================================================

    Core.h
    Created: 14 Mar 2015 3:30:39am
    Author:  adam

  ==============================================================================
*/

#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include "ICore.h"
#include <memory>

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
}

namespace jukebox { namespace core {

class Core : public ICore
{
public:
    Core();
    ~Core();
    
    void initialise(const String& name) override;
    void uninitialise() override;
    
private:
    void coinInserted50();
    void coinInserted100();
    void coinInserted200();
    
    void playingSong();
    void playingAlbum();
    
    void creditIncrease();
    void creditDecrease();
    
    void exitRequested();

private:
    jukebox::signals::Slot eventsSlot;

    std::unique_ptr<gui::IGui> gui;
    std::unique_ptr<creditmanager::ICreditManager> creditManager;
    unsigned int number;
};

}}

#endif  // CORE_H_INCLUDED
