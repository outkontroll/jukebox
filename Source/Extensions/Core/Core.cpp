/*
  ==============================================================================

    Core.cpp
    Created: 15 Mar 2015 1:37:31pm
    Author:  adam

  ==============================================================================
*/

#include "Core.h"
#include "Gui.h"
#include "CreditManager.h"
#include "MusicPlayer.h"
#include "Statistics.h"
#include "Formaters.h"

using namespace jukebox::core;
using namespace jukebox::gui;
using namespace jukebox::signals;
using namespace jukebox::audio;
using namespace jukebox::statistics;

const std::string EROOR_FEW_CREDITS_SONG = "Too few credits to play a song!";
const std::string EROOR_FEW_CREDITS_ALBUM = "Too few credits to play an album!";

Core::Core()
{
}

Core::~Core()
{
}

void Core::initialise(const std::string& name)
{
    gui.reset(new gui::Gui);
    eventsSlot.connect(this, &Core::coinInserted50, gui->coinInserted50Signal);
    eventsSlot.connect(this, &Core::coinInserted100, gui->coinInserted100Signal);
    eventsSlot.connect(this, &Core::coinInserted200, gui->coinInserted200Signal);
    eventsSlot.connect(this, &Core::playSong, gui->playSongSignal);
    eventsSlot.connect(this, &Core::playAlbum, gui->playAlbumSignal);
    eventsSlot.connect(this, &Core::creditIncrease, gui->creditIncreaseSignal);
    eventsSlot.connect(this, &Core::creditDecrease, gui->creditDecreaseSignal);
    eventsSlot.connect(this, &Core::exitRequested, gui->exitRequestedSignal);
    eventsSlot.connect(this, &Core::showStatistics, gui->showStatisticsSignal);
    gui->initialise(name);
    
    creditManager.reset(new creditmanager::CreditManager);
    musicPlayer.reset(new audio::MusicPlayer);
    statistics.reset(new statistics::Statistics);
    
    //TODO
    gui->setMusicFolder("001");
}

void Core::uninitialise()
{
    gui->uninitialise();
    gui = nullptr;
    
    creditManager = nullptr;
    
    musicPlayer = nullptr;
    
    statistics = nullptr;
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
    if(! creditManager->hasEnoughCreditsToPlaySong())
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
    if(! creditManager->hasEnoughCreditsToPlayAlbum())
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
    juce::JUCEApplication::quit();
}

void Core::showStatistics()
{
    statistics->showStatistics();
}
