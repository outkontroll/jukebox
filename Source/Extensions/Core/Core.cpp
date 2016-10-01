/*
  ==============================================================================

    Core.cpp
    Created: 15 Mar 2015 1:37:31pm
    Author:  adam

  ==============================================================================
*/

//TODO: remove this include by signaling the exit request
#include "Core.h"
#include "IGui.h"
#include "ICreditManager.h"
#include "IMusicPlayer.h"
#include "IStatistics.h"
#include "Formaters.h"
#include "Logger.h"

using namespace jukebox::core;
using namespace jukebox::gui;
using namespace jukebox::signals;
using namespace jukebox::audio;
using namespace jukebox::statistics;

const std::string EROOR_FEW_CREDITS_SONG = "Too few credits to play a song!";
const std::string EROOR_FEW_CREDITS_ALBUM = "Too few credits to play an album!";

void Core::initialize(const std::string& name,
                      const std::shared_ptr<gui::IGui>& iGui,
                      const std::shared_ptr<creditmanager::ICreditManager>& iCreditManager,
                      const std::shared_ptr<audio::IMusicPlayer>& iMusicPlayer,
                      const std::shared_ptr<statistics::IStatistics>& iStatistics)
{
    gui = iGui;
    eventsSlot.connect(this, &Core::coinInserted50, gui->coinInserted50Signal);
    eventsSlot.connect(this, &Core::coinInserted100, gui->coinInserted100Signal);
    eventsSlot.connect(this, &Core::coinInserted200, gui->coinInserted200Signal);
    eventsSlot.connect(this, &Core::playSong, gui->playSongSignal);
    eventsSlot.connect(this, &Core::playAlbum, gui->playAlbumSignal);
    eventsSlot.connect(this, &Core::removePlayedSong, gui->removePlayedSongSignal);
    eventsSlot.connect(this, &Core::creditIncrease, gui->creditIncreaseSignal);
    eventsSlot.connect(this, &Core::creditDecrease, gui->creditDecreaseSignal);
    eventsSlot.connect(this, &Core::exitRequested, gui->exitRequestedSignal);
    eventsSlot.connect(this, &Core::showStatistics, gui->showStatisticsSignal);
    gui->initialize(name);
    
    creditManager = iCreditManager;
    musicPlayer = iMusicPlayer;
    statistics = iStatistics;
    
    //TODO
    gui->setMusicFolder("001");
    
    LOG_INFO("done");
}

void Core::uninitialize()
{
    gui->uninitialize();
    
    gui = nullptr;
    creditManager = nullptr;
    musicPlayer = nullptr;
    statistics = nullptr;
    
    LOG_INFO("done");
}

void Core::coinInserted50()
{
    creditManager->coinInsert50();
    gui->refreshCredits(creditManager->getCredits());
}

void Core::coinInserted100()
{
    creditManager->coinInsert100();
    gui->refreshCredits(creditManager->getCredits());
}

void Core::coinInserted200()
{
    creditManager->coinInsert200();
    gui->refreshCredits(creditManager->getCredits());
}
    
void Core::playSong(Song song)
{   
    if(!creditManager->hasEnoughCreditsToPlaySong())
    {
        gui->showStatusMessage(EROOR_FEW_CREDITS_SONG);
    }
    else
    {
        creditManager->startPlaySong();
        musicPlayer->playSong(song);
        statistics->songPlayed(song);
        gui->refreshCredits(creditManager->getCredits());
        gui->enqueue(FillWithLeadingZeros(song.getAlbum(), 3) + FillWithLeadingZeros(song.getSong(), 2));
    }
}

void Core::playAlbum(Song album)
{
    if(!creditManager->hasEnoughCreditsToPlayAlbum())
    {
        gui->showStatusMessage(EROOR_FEW_CREDITS_ALBUM);
    }
    else
    {
        creditManager->startPlayAlbum();
        musicPlayer->playAlbum(album);
        statistics->albumPlayed(album);
        gui->refreshCredits(creditManager->getCredits());
        gui->enqueue(FillWithLeadingZeros(album.getAlbum(), 3));
    }
}

void Core::removePlayedSong()
{
    musicPlayer->stopPlaying();
    gui->removeNextSong();
}
    
void Core::creditIncrease()
{
    creditManager->creditIncrease();
    gui->refreshCredits(creditManager->getCredits());
}

void Core::creditDecrease()
{
    creditManager->creditDecrease();
    gui->refreshCredits(creditManager->getCredits());
}
    
void Core::exitRequested()
{
    LOG_INFO("");
    exitRequestedSignal();
}

void Core::showStatistics()
{
    statistics->showStatistics();
}
