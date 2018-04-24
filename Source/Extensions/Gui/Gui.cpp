#include "Gui.h"
#include "MainWindow.h"
#include "MainComponent.h"
#include "SongBuilder.h"
#include "Logger.h"
#include "Song.h"
#include "ResourceId.h"
#include "ResourceString.h"
#include "JukeboxTimer.h"
#include <algorithm>
#include <numeric>
//TODO remove this as this is just for testing purposes
#include <array>

using namespace jukebox;
using namespace jukebox::gui;
using namespace jukebox::signals;
using namespace jukebox::audio;
using namespace jukebox::songbuilder;
using namespace juce;

namespace {
    constexpr unsigned int defaultAlbumIndex = 1;
    constexpr unsigned int defaultSongIndex = 0;

    //TODO remove this as this is just for testing purposes
    const std::array<unsigned, 3> filesToPlay = {{ 1, 16, 4 }};
}

Gui::Gui(const std::string& applicationName)
    : mainComponent(std::make_unique<MainComponent>()),
      mainWindow(std::make_unique<MainWindow>(applicationName, mainComponent.get()))
{
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
    //TODO these two are here just for testing!
    else if(textCharacter == 'x')
    {
        static unsigned int fileToPlay = 0;
        ++fileToPlay;
        fileToPlay = fileToPlay % 3;
        //TODO
        playSongSignal(SongBuilder::buildSong(7, filesToPlay[fileToPlay], musicFolder, *fileSys));
    }
    else if(textCharacter == 'v')
    {
        //TODO
        //playAlbumSignal(Album(12));
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

void Gui::setMusicFolder(const std::string& folder)
{
    musicFolder = folder;
    //these two is needed if we set another folder during runtime
    visibleAlbumsIndex = defaultAlbumIndex;
    selectedAlbumIndex = defaultAlbumIndex;
    selectedSongIndex = defaultSongIndex;
    mainComponent->loadMultipleAlbums(musicFolder, visibleAlbumsIndex, *fileSys);
    mainComponent->loadSingleAlbum(musicFolder, selectedAlbumIndex, *fileSys);
    mainComponent->updateAlbumSelection(selectedAlbumIndex);
    mainComponent->updateSongSelection(selectedSongIndex);
    mainComponent->setMusicDirectory(musicFolder);
}

void Gui::setTimeToPlaySong(int millisecs)
{
    timeToPlaySong = millisecs;
    mainComponent->setTimeToPlayASong(timeToPlaySong);
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
    ++selectedAlbumIndex;
    if(selectedAlbumIndex >= visibleAlbumsIndex + albumIndexStep)
    {
        selectedAlbumIndex = visibleAlbumsIndex;
    }

    selectedSongIndex = defaultSongIndex;
    mainComponent->loadSingleAlbum(musicFolder, selectedAlbumIndex, *fileSys);
    mainComponent->updateAlbumSelection(selectedAlbumIndex);
    mainComponent->updateSongSelection(selectedSongIndex);
}

void Gui::stepSelectionSingleAlbumMode()
{
    ++selectedSongIndex;

    //TODO: handle proper overflow
    if(selectedSongIndex > visibleSongsIndex)
        selectedSongIndex = 0;

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

    mainComponent->updateAlbumSelection(selectedAlbumIndex);
    selectedSongIndex = defaultSongIndex;
    mainComponent->updateSongSelection(selectedSongIndex);
}

void Gui::handleAlbumSwitchInMultipleAlbumsMode(bool increase)
{
    visibleAlbumsIndex = getNextVisibleAlbumsIndex(visibleAlbumsIndex, increase);
    mainComponent->loadMultipleAlbums(musicFolder, visibleAlbumsIndex, *fileSys);

    selectedAlbumIndex = visibleAlbumsIndex;
    mainComponent->loadSingleAlbum(musicFolder, selectedAlbumIndex, *fileSys);
}

void Gui::handleUserInputNumbers(char number)
{
    if(userInputSongNumber.length() >= 5)
        return;

    userInputSongNumber += number;
    mainComponent->setCurrentUserInputNumber(userInputSongNumber);

    if(userInputSongNumber.length() == 5)
    {
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
        mainComponent->setCurrentUserInputNumber(SongBuilder::createVisibleName(selectedAlbumIndex, selectedSongIndex + 1));
        playSongWithDelay(selectedAlbumIndex, selectedSongIndex + 1);
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

void Gui::playSongWithDelay(unsigned int albumNumber, unsigned int songNumber)
{
    const auto song = SongBuilder::buildSong(albumNumber, songNumber, musicFolder, *fileSys);
    if(!song.fileName.empty())
    {
        secondsToPlayTimer = std::make_unique<JukeboxTimer>([this, song](){
            playSongSignal(song);
            userInputSongNumber = "";
            mainComponent->setCurrentUserInputNumber(userInputSongNumber);

            secondsToPlayTimer.reset();
        });

        secondsToPlayTimer->startTimer(timeToPlaySong);
    }
    else
    {
        showStatusMessage(ResourceId::ErrorSongNotExists);

        userInputSongNumber = "";
        mainComponent->setCurrentUserInputNumber(userInputSongNumber);
    }
}

void Gui::playAlbumWithDelay(unsigned int albumNumber)
{
    const auto songs = SongBuilder::buildSongsInAlbum(albumNumber, musicFolder, *fileSys);
    if(!songs.empty())
    {
        secondsToPlayTimer = std::make_unique<JukeboxTimer>([this, songs](){
            playAlbumSignal(songs);
            userInputSongNumber = "";
            mainComponent->setCurrentUserInputNumber(userInputSongNumber);

            secondsToPlayTimer.reset();
        });

        secondsToPlayTimer->startTimer(timeToPlaySong);
    }
    else
    {
        showStatusMessage(ResourceId::ErrorDuringAlbumPlaying);

        userInputSongNumber = "";
        mainComponent->setCurrentUserInputNumber(userInputSongNumber);
    }
}

void Gui::handleAlbumSwitchInSingleAlbumMode(bool increase)
{
    selectedAlbumIndex = getNextSelectedAlbumIndex(selectedAlbumIndex, increase);
    mainComponent->loadSingleAlbum(musicFolder, selectedAlbumIndex, *fileSys);

    if((increase && selectedAlbumIndex >= visibleAlbumsIndex + albumIndexStep) ||
       (!increase && selectedAlbumIndex < visibleAlbumsIndex))
    {
        visibleAlbumsIndex = getNextVisibleAlbumsIndex(visibleAlbumsIndex, increase);
        mainComponent->loadMultipleAlbums(musicFolder, visibleAlbumsIndex, *fileSys);
    }
}

unsigned int Gui::getNextVisibleAlbumsIndex(unsigned int currentVisibleAlbumsIndex, bool increase) const
{
    if(increase)
        currentVisibleAlbumsIndex += albumIndexStep;
    else
        currentVisibleAlbumsIndex -= albumIndexStep;

    //TODO check underflow

    return currentVisibleAlbumsIndex;
}

unsigned int Gui::getNextSelectedAlbumIndex(unsigned int currentSelectedAlbumIndex, bool increase) const
{
    if(increase)
        ++currentSelectedAlbumIndex;
    else
        --currentSelectedAlbumIndex;

    //TODO check underflow

    return currentSelectedAlbumIndex;
}
