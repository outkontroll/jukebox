#include "Core.h"
#include "IGui.h"
#include "ICreditManager.h"
#include "IMusicPlayer.h"
#include "IStatistics.h"
#include "ISettings.h"
#include "Logger.h"
#include "MusicPlayerExceptions.h"
#include <iostream>

using namespace jukebox;
using namespace jukebox::core;
using namespace jukebox::gui;
using namespace jukebox::signals;
using namespace jukebox::audio;
using namespace jukebox::statistics;
using namespace jukebox::settings;

namespace {
    const std::string ErrorFewCreditsSong = "Too few credits to play a song!";
    const std::string ErrorFewCreditsAlbum = "Too few credits to play an album!";
    const std::string ErrorDuringSongPlaying = "An unexpected error occured during playing song: ";
}

Core::Core(std::unique_ptr<gui::IGui> iGui,
           std::unique_ptr<creditmanager::ICreditManager> iCreditManager,
           std::unique_ptr<audio::IMusicPlayer> iMusicPlayer,
           std::unique_ptr<statistics::IStatistics> iStatistics,
           std::unique_ptr<settings::ISettings> iSettings)
    : gui(std::move(iGui)),
      creditManager(std::move(iCreditManager)),
      musicPlayer(std::move(iMusicPlayer)),
      statistics(std::move(iStatistics)),
      settings(std::move(iSettings))
{
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
    eventsSlot.connect(this, &Core::playNextSong, gui->playNextSongSignal);

    eventsSlot.connect(this, &Core::finishedPlaying, musicPlayer->finishedPlayingSignal);
    gui->setMusicFolder(settings->getMusicDirectory());
}

void Core::coinInserted50()
{
    creditManager->coinInsert50();
    gui->refreshCredits(creditManager->getCredits());
    statistics->coinInserted50();
}

void Core::coinInserted100()
{
    creditManager->coinInsert100();
    gui->refreshCredits(creditManager->getCredits());
    statistics->coinInserted100();
}

void Core::coinInserted200()
{
    creditManager->coinInsert200();
    gui->refreshCredits(creditManager->getCredits());
    statistics->coinInserted200();
}

void Core::playSong(const Song& song)
{
    if(!creditManager->hasEnoughCreditsToPlaySong())
    {
        gui->showStatusMessage(ErrorFewCreditsSong);
    }
    else
    {
        creditManager->startPlaySong();
        gui->refreshCredits(creditManager->getCredits());
        statistics->songPlayed(song);

        try
        {
            if(!musicPlayer->isPlaying())
            {
                musicPlayer->playSong(song.getFileName());
            }

            gui->enqueue(song);
        }
        catch(MusicPlayerException&)
        {
        }
    }
}

void Core::playAlbum(Album album)
{
    if(!creditManager->hasEnoughCreditsToPlayAlbum())
    {
        gui->showStatusMessage(ErrorFewCreditsAlbum);
    }
    else
    {
        creditManager->startPlayAlbum();
        gui->refreshCredits(creditManager->getCredits());
        statistics->albumPlayed(album);

        //TODO play an album
        //for(Song song : album)
        //musicPlayer->playSong(song);
        Song song(album, 0, "albumTesting");
        gui->enqueue(song);
    }
}

void Core::removePlayedSong()
{
    musicPlayer->stopPlaying();
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
    //TODO: use file
    statistics->showStatistics(std::cout);
}

void Core::playNextSong(const Song& song)
{
    try
    {
        musicPlayer->playSong(song.getFileName());
    }
    catch(MusicPlayerException&)
    {
        gui->showStatusMessage(ErrorDuringSongPlaying + song.toString());
        gui->removeCurrentSong();
    }
}

void Core::finishedPlaying()
{
    gui->removeCurrentSong();
}
