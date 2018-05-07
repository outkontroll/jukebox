#include "Core.h"
#include "IGui.h"
#include "ICreditManager.h"
#include "IMusicPlayer.h"
#include "IStatistics.h"
#include "ISettings.h"
#include "IFileSystem.h"
#include "Logger.h"
#include "MusicPlayerExceptions.h"
#include "SongBuilder.h"
#include "Song.h"
#include "ResourceId.h"
#include <iostream>

using namespace jukebox;
using namespace jukebox::core;
using namespace jukebox::gui;
using namespace jukebox::signals;
using namespace jukebox::audio;
using namespace jukebox::statistics;
using namespace jukebox::settings;
using namespace jukebox::songbuilder;

Core::Core(std::unique_ptr<gui::IGui> iGui,
           std::unique_ptr<creditmanager::ICreditManager> iCreditManager,
           std::unique_ptr<audio::IMusicPlayer> iMusicPlayer,
           std::unique_ptr<statistics::IStatistics> iStatistics,
           std::unique_ptr<settings::ISettings> iSettings,
           std::unique_ptr<filesystem::IFileSystem> iFileSystem)
    : gui(std::move(iGui)),
      creditManager(std::move(iCreditManager)),
      musicPlayer(std::move(iMusicPlayer)),
      statistics(std::move(iStatistics)),
      settings(std::move(iSettings)),
      fileSys(std::move(iFileSystem))
{
    eventsSlot.connect(this, &Core::coinInserted50, gui->coinInserted50Signal);
    eventsSlot.connect(this, &Core::coinInserted100, gui->coinInserted100Signal);
    eventsSlot.connect(this, &Core::coinInserted200, gui->coinInserted200Signal);
    eventsSlot.connect(this, &Core::creditIncrease, gui->creditIncreaseSignal);
    eventsSlot.connect(this, &Core::creditDecrease, gui->creditDecreaseSignal);
    eventsSlot.connect(this, &Core::playSong, gui->playSongSignal);
    eventsSlot.connect(this, &Core::playAlbum, gui->playAlbumSignal);
    eventsSlot.connect(this, &Core::removePlayedSong, gui->removePlayedSongSignal);
    eventsSlot.connect(this, &Core::playNextSong, gui->playNextSongSignal);
    eventsSlot.connect(this, &Core::musicDirectoryChanged, gui->musicDirectoryChangedSignal);
    eventsSlot.connect(this, &Core::timeToPlayASongChanged, gui->timeToPlayASongChangedSignal);
    eventsSlot.connect(this, &Core::timeToSaveInsertedCoinsChanged, gui->timeToSaveInsertedCoinsChangedSignal);
    eventsSlot.connect(this, &Core::showStatisticsRequested, gui->requestStatisticsSignal);
    eventsSlot.connect(this, &Core::exitRequested, gui->exitRequestedSignal);

    eventsSlot.connect(this, &Core::finishedPlaying, musicPlayer->finishedPlayingSignal);
    gui->setFileSystem(fileSys.get());
    gui->setMusicFolder(settings->getMusicDirectory());
    gui->setTimeToPlaySong(settings->getTimeToPlaySong());
    gui->setTimeToSaveInsertedCoins(settings->getTimeToSaveInsertedCoins());
    statistics->setSaveTimeout(settings->getTimeToSaveInsertedCoins());
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
        gui->showStatusMessage(ResourceId::ErrorFewCreditsSong);
        return;
    }

    creditManager->startPlaySong();
    gui->refreshCredits(creditManager->getCredits());
    statistics->songPlayed(song);

    playOrEnqueue(song);
}

void Core::playAlbum(const Album& album, const std::vector<Song>& songs)
{
    if(!creditManager->hasEnoughCreditsToPlayAlbum())
    {
        gui->showStatusMessage(ResourceId::ErrorFewCreditsAlbum);
        return;
    }

    if(album.albumNumber == 0)
    {
        gui->showStatusMessage(ResourceId::ErrorDuringAlbumPlaying);
        return;
    }

    if(songs.empty())
    {
        gui->showStatusMessage(ResourceId::ErrorDuringAlbumPlaying);
        return;
    }

    creditManager->startPlayAlbum();
    gui->refreshCredits(creditManager->getCredits());

    statistics->albumPlayed(album);

    for(const auto& song : songs)
    {
        statistics->songPlayed(song);
        playOrEnqueue(song);
    }
}

void Core::removePlayedSong()
{
    if(musicPlayer->isPlaying())
    {
        musicPlayer->stopPlaying();
    }
    else
    {
        gui->showStatusMessage(ResourceId::WarningNotPlayingSong);
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
    LOG_INFO("");

    if(musicPlayer->isPlaying())
    {
        gui->prepareForExit();
        musicPlayer->stopPlaying();
    }

    exitRequestedSignal();
}

void Core::musicDirectoryChanged(const std::string& newMusicDirectory)
{
    settings->setMusicDirectory(newMusicDirectory);
    gui->setMusicFolder(newMusicDirectory);
}

void Core::timeToPlayASongChanged(int millisecs)
{
    if(millisecs >= 0)
    {
        settings->setTimeToPlaySong(millisecs);
        gui->setTimeToPlaySong(millisecs);
    }
    else
    {
        gui->showStatusMessage(ResourceId::ErrorNegativeNumber);
    }
}

void Core::timeToSaveInsertedCoinsChanged(int millisecs)
{
    if(millisecs >= 3600)
    {
        settings->setTimeToSaveInsertedCoins(millisecs);
        statistics->setSaveTimeout(millisecs);
        gui->setTimeToSaveInsertedCoins(millisecs);
    }
    else
    {
        gui->showStatusMessage(ResourceId::ErrorWrongNumber);
    }
}

void Core::showStatisticsRequested()
{
    std::stringstream ss;
    statistics->showStatistics(ss);
    gui->showStatistics(ss.str());
}

void Core::playNextSong(const Song& song)
{
    if(musicPlayer->isPlaying())
    {
        LOG_ERROR("MusicPlayer is currently playing, tried to play: " << song.visibleName);
        gui->showStatusMessage(ResourceId::ErrorDuringSongPlaying);
        return;
    }

    try
    {
        musicPlayer->playSong(song.fileName);
        gui->setCurrentlyPlayedSong(song);
    }
    catch(MusicPlayerException&)
    {
        gui->showStatusMessage(ResourceId::ErrorDuringSongPlaying/*, song.toString()*/);
        gui->removeCurrentSong();
    }
}

void Core::playOrEnqueue(const Song& song)
{
    try
    {
        if(!musicPlayer->isPlaying())
        {
            musicPlayer->playSong(song.fileName);
            gui->setCurrentlyPlayedSong(song);
        }
        else
        {
            gui->enqueue(song);
        }
    }
    catch(MusicPlayerException&)
    {
        LOG_ERROR("Song playing is unsuccessful, song: " << song.visibleName);
        gui->showStatusMessage(ResourceId::ErrorDuringSongPlaying);
    }
}

void Core::finishedPlaying()
{
    gui->removeCurrentSong();
}
