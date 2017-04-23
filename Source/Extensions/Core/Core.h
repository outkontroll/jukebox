#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include <memory>
#include "Signals.hpp"
#include "Song.h"

namespace jukebox {

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

namespace core {

class Core
{
public:
    Core(std::unique_ptr<gui::IGui> iGui,
         std::unique_ptr<creditmanager::ICreditManager> iCreditManager,
         std::unique_ptr<audio::IMusicPlayer> iMusicPlayer,
         std::unique_ptr<statistics::IStatistics> iStatistics);

    //TODO: this should be private
    jukebox::signals::Signal<> exitRequestedSignal;

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

    void finishedPlaying();

private:
    jukebox::signals::Slot eventsSlot;

    std::unique_ptr<gui::IGui> gui;
    std::unique_ptr<creditmanager::ICreditManager> creditManager;
    std::unique_ptr<audio::IMusicPlayer> musicPlayer;
    std::unique_ptr<statistics::IStatistics> statistics;
};

}}

#endif  // CORE_H_INCLUDED
