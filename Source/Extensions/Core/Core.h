#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include <memory>
#include "ICore.h"
#include "Signals.hpp"
#include "Song.h"

namespace jukebox { namespace core {

class Core : public ICore
{
public:
    Core(const std::string& name,
         std::unique_ptr<gui::IGui> iGui,
         std::unique_ptr<creditmanager::ICreditManager> iCreditManager,
         std::unique_ptr<audio::IMusicPlayer> iMusicPlayer,
         std::unique_ptr<statistics::IStatistics> iStatistics);
    ~Core();

private:
    void coinInserted50();
    void coinInserted100();
    void coinInserted200();
    
    void playSong(audio::Song);
    void playAlbum(audio::Album);
    void removePlayedSong();
    
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
