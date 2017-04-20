#include "Core.h"
#include "IGui.h"
#include "ICreditManager.h"
#include "IMusicPlayer.h"
#include "IStatistics.h"
#include "Formaters.h"
#include "Logger.h"
#include <iostream>
//TODO remove this as this is just for testing purposes
#include <array>

using namespace jukebox::core;
using namespace jukebox::gui;
using namespace jukebox::signals;
using namespace jukebox::audio;
using namespace jukebox::statistics;

namespace {
    const std::string ERROR_FEW_CREDITS_SONG = "Too few credits to play a song!";
    const std::string ERROR_FEW_CREDITS_ALBUM = "Too few credits to play an album!";

    const std::array<std::string, 3> filesToPlay = { "/home/adam/Music/test_data/wav/AUTORUN.WAV",
                                                     "/home/adam/Music/test_data/Mp3/MAINMENU.MP3",
                                                     "/home/adam/Music/test_data/Mp3/LoopLepr.mp3"};

}

std::string calculateFileName(Song song);

Core::Core(std::unique_ptr<gui::IGui> iGui,
           std::unique_ptr<creditmanager::ICreditManager> iCreditManager,
           std::unique_ptr<audio::IMusicPlayer> iMusicPlayer,
           std::unique_ptr<statistics::IStatistics> iStatistics)
    : gui(std::move(iGui)),
      creditManager(std::move(iCreditManager)),
      musicPlayer(std::move(iMusicPlayer)),
      statistics(std::move(iStatistics))
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

    gui->setMusicFolder("001");
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
        gui->showStatusMessage(ERROR_FEW_CREDITS_SONG);
    }
    else
    {
        creditManager->startPlaySong();
        musicPlayer->playSong(calculateFileName(song));
        statistics->songPlayed(song);
        gui->refreshCredits(creditManager->getCredits());
        gui->enqueue(FillWithLeadingZeros(song.getAlbumNumber(), 3) + FillWithLeadingZeros(song.getSongNumber(), 2));
    }
}

void Core::playAlbum(Album album)
{
    if(!creditManager->hasEnoughCreditsToPlayAlbum())
    {
        gui->showStatusMessage(ERROR_FEW_CREDITS_ALBUM);
    }
    else
    {
        creditManager->startPlayAlbum();
        //TODO play an album
        //for(Song song : album)
        //musicPlayer->playSong(song);
        statistics->albumPlayed(album);
        gui->refreshCredits(creditManager->getCredits());
        gui->enqueue(FillWithLeadingZeros(album.getAlbumNumber(), 3));
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
    //TODO: use file
    statistics->showStatistics(std::cout);
}

std::string calculateFileName(Song /*song*/)
{
    //TODO: get the actual filename of the song
    static int fileToPlay = 0;
    fileToPlay = fileToPlay % 3;
    return filesToPlay[fileToPlay++];
}
