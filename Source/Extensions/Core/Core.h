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
#include "Song.h"
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

class Core : public ICore
{
public:
    Core();
    ~Core();
    
    void initialise(const String&) override;
    void uninitialise() override;
    
private:
    void coinInserted50();
    void coinInserted100();
    void coinInserted200();
    
    void playSong(audio::Song);
    void playAlbum(audio::Song);
    
    void creditIncrease();
    void creditDecrease();
    
    void exitRequested();
    
    void showStatistics();

private:
    jukebox::signals::Slot eventsSlot;

    std::unique_ptr<gui::IGui> gui;
    std::unique_ptr<creditmanager::ICreditManager> creditManager;
    std::unique_ptr<audio::IMusicPlayer> musicPlayer;
    std::unique_ptr<statistics::IStatistics> statistics;
};

}}

#endif  // CORE_H_INCLUDED
