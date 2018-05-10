#include "Gui.h"
#include <algorithm>
#include <numeric>
#include "MainWindow.h"
#include "MainComponent.h"
#include "SongBuilder.h"
#include "Logger.h"
#include "Song.h"
#include "ResourceId.h"
#include "ResourceString.h"
#include "JukeboxTimer.h"
#include "IFileSystem.h"
#include "AlbumStepCalculator.h"

using namespace jukebox;
using namespace jukebox::gui;
using namespace jukebox::signals;
using namespace jukebox::audio;
using namespace jukebox::songbuilder;
using namespace juce;

namespace {
    constexpr unsigned int defaultAlbumIndex = 1;
    constexpr unsigned int defaultSongIndex = 0;
}

Gui::Gui(const std::string& applicationName)
    : mainComponent(std::make_unique<MainComponent>()),
      mainWindow(std::make_unique<MainWindow>(applicationName, mainComponent.get()))
{
    mainWindow->setFullScreen(true);

    connectSignals();
}


Gui::Gui(std::unique_ptr<MainComponent> mainComp)
    : mainComponent(std::move(mainComp))
{
    connectSignals();
}

Gui::~Gui() = default;

void Gui::connectSignals()
{
    eventsSlot.connect(this, &Gui::keyPressed, mainComponent->keyPressedSignal);
    eventsSlot.connect(this, &Gui::playNextSong, mainComponent->playNextSongSignal);
    eventsSlot.connect(this, &Gui::musicDirectoryChanged, mainComponent->musicDirectoryChangedSignal);
    eventsSlot.connect(this, &Gui::timeToPlayASongChanged, mainComponent->timeToPlayASongChangedSignal);
    eventsSlot.connect(this, &Gui::timeToSaveInsertedCoinsChanged, mainComponent->timeToSaveInsertedCoinsChangedSignal);
}

void Gui::keyPressed(const KeyPress& key)
{
    const auto keyCode = key.getKeyCode();
    const auto textCharacter = key.getTextCharacter();

    //TODO enable this
    //LOG_INFO("***USER*** " << key.getTextDescription() << ", keyCode: " << keyCode << ", textCharacter: " << textCharacter);

    if(keyCode == KeyPress::F4Key)
    {
        exitRequestedSignal();
    }
    else if(keyCode == KeyPress::escapeKey)
    {
        switchBetweenUserModes();
    }
    else if(keyCode == KeyPress::backspaceKey)
    {
        removePlayedSongSignal();
    }
    else if(textCharacter == '+')
    {
        handleAlbumSwitchInAllAlbumMode(false);
    }
    else if(textCharacter == '-')
    {
        handleAlbumSwitchInAllAlbumMode(true);
    }
    else if(textCharacter == '0' ||
            textCharacter == '1' ||
            textCharacter == '2' ||
            textCharacter == '3' ||
            textCharacter == '4' ||
            textCharacter == '5' ||
            textCharacter == '6' ||
            textCharacter == '7' ||
            textCharacter == '8' ||
            textCharacter == '9')
    {
        handleUserInputNumbers(static_cast<char>(textCharacter));
    }

    else if(textCharacter == 'a')
    {
        increaseSoundVolumeSignal();
    }
    else if(textCharacter == 's')
    {
        decreaseSoundVolumeSignal();
    }
    else if(textCharacter == 'm')
    {
        switchMuteStatusSignal();
    }
    else if(textCharacter == 'n')
    {
        showHelp();
    }
    else if(textCharacter == 'o')
    {
        coinInserted50Signal();
    }
    else if(textCharacter == 'p')
    {
        coinInserted100Signal();
    }
    else if(textCharacter == 'l')
    {
        coinInserted200Signal();
    }
    else if(textCharacter == 'k')
    {
        creditIncreaseSignal();
    }
    else if(textCharacter == 'j')
    {
        creditDecreaseSignal();
    }
    else if(textCharacter == 'q')
    {
        shutDownSignal();
    }
    else if(textCharacter == 'h')
    {
        switchBetweenAlbumModes();
    }
    else if(textCharacter == 'c')
    {
        stepSelection();
    }
    else if(textCharacter == '.')
    {
        handleDotPressed();
    }
}

void Gui::playNextSong(const Song& song)
{
    playNextSongSignal(song);
}

void Gui::refreshCredits(unsigned int credits)
{
    mainComponent->refreshCredits(credits);
}

void Gui::showStatusMessage(ResourceId messageId)
{
    mainComponent->showStatusMessage(Resources::getResourceStringFromId(messageId));
}

void Gui::setFileSystem(filesystem::IFileSystem* filesys)
{
    assert(filesys != nullptr);
    fileSys = filesys;
}

void Gui::showStatistics(const std::string& statistics)
{
    mainComponent->showStatistics(statistics);
}

void Gui::loadMultipleAlbums()
{
    mainComponent->loadMultipleAlbums(fileSys->getAlbums(), visibleAlbumsId);
}

void Gui::loadSingleAlbum()
{
    mainComponent->loadSingleAlbum(fileSys->getAlbums(), selectedAlbumId);
}

void Gui::setMusicFolder(const std::string& folder)
{
    musicFolder = folder;

    //these two is needed if we set another folder during runtime
    visibleAlbumsId = defaultAlbumIndex;
    selectedAlbumId = defaultAlbumIndex;
    selectedSongIndex = defaultSongIndex;
    loadMultipleAlbums();
    loadSingleAlbum();
    mainComponent->updateAlbumSelection(selectedAlbumId);
    mainComponent->updateSongSelection(selectedSongIndex);
    mainComponent->setMusicDirectory(musicFolder);
}

void Gui::setTimeToPlaySong(int millisecs)
{
    timeToPlaySong = millisecs;
    mainComponent->setTimeToPlayASong(timeToPlaySong);
}

void Gui::setTimeToSaveInsertedCoins(int millisecs)
{
    mainComponent->setTimeToSaveInsertedCoins(millisecs);
}

void Gui::setCurrentlyPlayedSong(const audio::Song& song)
{
    mainComponent->setCurrentlyPlayedSong(song);
    mainComponent->showStatusMessage(Resources::getResourceStringFromId(ResourceId::Playing));
}

void Gui::enqueue(const audio::Song& song)
{
    mainComponent->enqueue(song);
}

void Gui::removeCurrentSong()
{
    mainComponent->removeCurrentSong();
}

void Gui::prepareForExit()
{
    mainComponent->prepareForExit();
}

void Gui::switchBetweenAlbumModes()
{
    if(!isInUserMode)
        return;

    isInMultipleAlbumsMode = !isInMultipleAlbumsMode;
    mainComponent->switchBetweenAlbumViews();
}

void Gui::switchBetweenUserModes()
{
    isInUserMode = !isInUserMode;
    mainComponent->switchBetweenUserModeViews();

    if(isInUserMode && !isInMultipleAlbumsMode)
    {
        mainComponent->switchBetweenAlbumViews();
    }

    if(!isInUserMode)
    {
        requestStatisticsSignal();
    }
}

void Gui::stepSelection()
{
    if(!isInMultipleAlbumsMode)
    {
        stepSelectionSingleAlbumMode();
    }
    else
    {
        stepSelectionMultipleAlbumsMode();
    }
}

void Gui::stepSelectionMultipleAlbumsMode()
{
    selectedAlbumId = static_cast<unsigned int>(AlbumStepCalculator{fileSys->getAlbums().size(), albumIndexStep}.getNextSelectedAlbumIdOnSamePage(visibleAlbumsId, selectedAlbumId));
    selectedSongIndex = defaultSongIndex;

    loadSingleAlbum();

    mainComponent->updateAlbumSelection(selectedAlbumId);
    mainComponent->updateSongSelection(selectedSongIndex);
}

void Gui::stepSelectionSingleAlbumMode()
{
    if(fileSys->getAlbums().empty())
        return;

    selectedSongIndex = static_cast<unsigned int>(SongStepCalculator().getNextSelectedSongIndex(fileSys->getAlbums()[selectedAlbumId - 1].songs.size(), selectedSongIndex));

    mainComponent->updateSongSelection(selectedSongIndex);
}

void Gui::showHelp()
{

}

void Gui::handleAlbumSwitchInAllAlbumMode(bool increase)
{
    if(isInMultipleAlbumsMode)
        handleAlbumSwitchInMultipleAlbumsMode(increase);
    else
        handleAlbumSwitchInSingleAlbumMode(increase);

    mainComponent->updateAlbumSelection(selectedAlbumId);
    selectedSongIndex = defaultSongIndex;
    mainComponent->updateSongSelection(selectedSongIndex);
}

void Gui::handleAlbumSwitchInMultipleAlbumsMode(bool increase)
{
    visibleAlbumsId = static_cast<unsigned int>(AlbumStepCalculator{fileSys->getAlbums().size(), albumIndexStep}.getNextVisibleAlbumsId(visibleAlbumsId, increase));
    loadMultipleAlbums();

    selectedAlbumId = visibleAlbumsId;
    loadSingleAlbum();
}

void Gui::handleUserInputNumbers(char number)
{
    if(userInputSongNumber.length() >= 5)
        return;

    userInputSongNumber += number;
    mainComponent->setCurrentUserInputNumber(userInputSongNumber);

    if(userInputSongNumber.length() == 5)
    {
        // the -1's are needed because number is 1 based and indices are 0 based
        unsigned int albumNumber = static_cast<unsigned int>(std::stoi(userInputSongNumber.substr(0, 3)));
        unsigned int songNumber = static_cast<unsigned int>(std::stoi(userInputSongNumber.substr(3)));
        if(songNumber != 0)
        {
            playSongWithDelay(albumNumber, songNumber);
        }
        else
        {
            playAlbumWithDelay(albumNumber);
        }
    }
}

void Gui::handleDotPressed()
{
    if(secondsToPlayTimer || isInMultipleAlbumsMode)
    {
        secondsToPlayTimer.reset();
        userInputSongNumber = "";
        mainComponent->setCurrentUserInputNumber(userInputSongNumber);
    }
    else if(!secondsToPlayTimer && !isInMultipleAlbumsMode)
    {
        mainComponent->setCurrentUserInputNumber(SongBuilder::createVisibleName(selectedAlbumId, selectedSongIndex + 1));
        playSongWithDelay(selectedAlbumId, selectedSongIndex + 1);
    }
}

void Gui::musicDirectoryChanged(const std::string& musicDirectory)
{
    musicDirectoryChangedSignal(musicDirectory);
}

void Gui::timeToPlayASongChanged(int millisecs)
{
    //TODO move?
    timeToPlayASongChangedSignal(std::move(millisecs));
}

void Gui::timeToSaveInsertedCoinsChanged(int millisecs)
{
    timeToSaveInsertedCoinsChangedSignal(std::move(millisecs));
}

void Gui::playSongWithDelay(unsigned int albumNumber, unsigned int songNumber)
{
    const unsigned int albumIndex = albumNumber - 1;
    const unsigned int songIndex = songNumber - 1;
    const auto& albums = fileSys->getAlbums();
    if(albumIndex >= albums.size() ||
       songIndex >= albums[albumIndex].songs.size())
    {
        showStatusMessage(ResourceId::ErrorSongNotExists);

        userInputSongNumber = "";
        mainComponent->setCurrentUserInputNumber(userInputSongNumber);

        return;
    }

    const auto& song = albums[albumIndex].songs[songIndex];

    secondsToPlayTimer = std::make_unique<JukeboxTimer>([this, song](){
        playSongSignal(song);
        userInputSongNumber = "";
        mainComponent->setCurrentUserInputNumber(userInputSongNumber);

        secondsToPlayTimer.reset();
    });

    secondsToPlayTimer->startTimer(timeToPlaySong);

}

void Gui::playAlbumWithDelay(unsigned int albumNumber)
{
    const unsigned int albumIndex = albumNumber - 1;
    const auto& albums = fileSys->getAlbums();
    if(albumIndex >= albums.size() ||
       albums[albumIndex].songs.empty())
    {
        showStatusMessage(ResourceId::ErrorDuringAlbumPlaying);

        userInputSongNumber = "";
        mainComponent->setCurrentUserInputNumber(userInputSongNumber);

        return;
    }

    const auto album = SongBuilder::buildAlbum(albumIndex + 1);
    const auto& songs = albums[albumIndex].songs;

    secondsToPlayTimer = std::make_unique<JukeboxTimer>([this, album, songs](){
        playAlbumSignal(album, songs);
        userInputSongNumber = "";
        mainComponent->setCurrentUserInputNumber(userInputSongNumber);

        secondsToPlayTimer.reset();
    });

    secondsToPlayTimer->startTimer(timeToPlaySong);
}

void Gui::handleAlbumSwitchInSingleAlbumMode(bool increase)
{
    const AlbumStepCalculator calc{fileSys->getAlbums().size(), albumIndexStep};
    selectedAlbumId = static_cast<unsigned int>(calc.getNextSelectedAlbumId(selectedAlbumId, increase));
    loadSingleAlbum();

    if(calc.shouldStepVisibleAlbums(visibleAlbumsId, selectedAlbumId, increase))
    {
        visibleAlbumsId = static_cast<unsigned int>(calc.getNextVisibleAlbumsId(visibleAlbumsId, increase));
        loadMultipleAlbums();
    }
}
