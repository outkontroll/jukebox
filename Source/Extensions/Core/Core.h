/*
  ==============================================================================

    Core.h
    Created: 14 Mar 2015 3:30:39am
    Author:  adam

  ==============================================================================
*/

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
    void initialize(const std::string& name,
                    const std::shared_ptr<gui::IGui>& iGui,
                    const std::shared_ptr<creditmanager::ICreditManager>& iCreditManager,
                    const std::shared_ptr<audio::IMusicPlayer>& iMusicPlayer,
                    const std::shared_ptr<statistics::IStatistics>& iStatistics) override;
    void uninitialize() override;
    
private:
    void coinInserted50();
    void coinInserted100();
    void coinInserted200();
    
    void playSong(audio::Song);
    void playAlbum(audio::Song);
    void removePlayedSong();
    
    void creditIncrease();
    void creditDecrease();
    
    void exitRequested();
    
    void showStatistics();

private:
    jukebox::signals::Slot eventsSlot;

    std::shared_ptr<gui::IGui> gui;
    std::shared_ptr<creditmanager::ICreditManager> creditManager;
    std::shared_ptr<audio::IMusicPlayer> musicPlayer;
    std::shared_ptr<statistics::IStatistics> statistics;
};

}}

#endif  // CORE_H_INCLUDED
