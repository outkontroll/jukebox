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

using namespace jukebox::core;
using namespace jukebox::gui;
using namespace jukebox::signals;
using namespace jukebox::audio;
using namespace jukebox::statistics;

Core::Core()
{
}

Core::~Core()
{
}

void Core::initialise(const String& name)
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
    eventsSlot.connect(this, &Core::printStatistics, gui->printStatisticsSignal);
    gui->initialise(name);
    
    creditManager.reset(new creditmanager::CreditManager);
    musicPlayer.reset(new audio::MusicPlayer);
    statistics.reset(new statistics::Statistics);
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
        gui->showStatusMessage("Too few credits to play a song!");
    }
    else
    {
        creditManager->startPlaySong();
        musicPlayer->playSong(song);
        statistics->songPlayed(song);
        gui->refreshCredits(creditManager->getCredits());
    }
}

void Core::playAlbum(Song album)
{
    if(! creditManager->hasEnoughCreditsToPlayAlbum())
    {
        gui->showStatusMessage("Too few credits to play an album!");
    }
    else
    {
        creditManager->startPlayAlbum();
        musicPlayer->playAlbum(album);
        statistics->albumPlayed(album);
        gui->refreshCredits(creditManager->getCredits());
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
    JUCEApplication::quit();
}

void Core::printStatistics()
{
    statistics->printStatistics();
}
