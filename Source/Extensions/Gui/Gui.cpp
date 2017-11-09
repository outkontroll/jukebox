#include "Gui.h"
#include "MainWindow.h"
#include "MainComponent.h"
#include "SongBuilder.h"
#include "FileSystem.h"
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
using namespace jukebox::filesystem;
using namespace jukebox::songbuilder;
using namespace juce;

namespace {
    static const unsigned int defaultAlbumIndex = 1;
    constexpr int timeToPlay = 5000;

    //TODO remove this as this is just for testing purposes
    const std::array<unsigned, 3> filesToPlay = {{ 1, 16, 4 }};
}

Gui::Gui(const std::string& applicationName)
    : mainComponent(std::make_unique<MainComponent>()),
      mainWindow(std::make_unique<MainWindow>(applicationName, mainComponent.get()))
{
    eventsSlot.connect(this, &Gui::keyPressed, mainComponent->keyPressedSignal);
    eventsSlot.connect(this, &Gui::playNextSong, mainComponent->playNextSongSignal);
}

Gui::Gui(std::unique_ptr<MainComponent> mainComp)
    : mainComponent(std::move(mainComp))
{
    eventsSlot.connect(this, &Gui::keyPressed, mainComponent->keyPressedSignal);
    eventsSlot.connect(this, &Gui::playNextSong, mainComponent->playNextSongSignal);
}

Gui::~Gui() = default;

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
        showStatisticsSignal();
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
        handleUserInputNumbers(textCharacter);
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
        static int fileToPlay = 0;
        ++fileToPlay;
        fileToPlay = fileToPlay % 3;
        //TODO
        playSongSignal(SongBuilder::buildSong(7, filesToPlay[fileToPlay], musicFolder));
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

void Gui::setMusicFolder(const std::string& folder)
{
    musicFolder = folder;
    //these two is needed if we set another folder during runtime
    visibleAlbumsIndex = defaultAlbumIndex;
    selectedAlbumIndex = defaultAlbumIndex;
    mainComponent->loadMultipleAlbums(musicFolder, visibleAlbumsIndex);
    mainComponent->loadSingleAlbum(musicFolder, selectedAlbumIndex);
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
    isInMultipleAlbumsMode = !isInMultipleAlbumsMode;
    mainComponent->switchBetweenAlbumViews();
}

void Gui::stepSelection()
{
    if(!isInMultipleAlbumsMode)
    {
        return;
    }

    ++selectedAlbumIndex;
    if(selectedAlbumIndex >= visibleAlbumsIndex + albumIndexStep)
    {
        selectedAlbumIndex = visibleAlbumsIndex;
    }

    mainComponent->loadSingleAlbum(musicFolder, selectedAlbumIndex);
    mainComponent->updateSelection(selectedAlbumIndex);
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

    mainComponent->updateSelection(selectedAlbumIndex);
}

void Gui::handleAlbumSwitchInMultipleAlbumsMode(bool increase)
{
    visibleAlbumsIndex = getNextVisibleAlbumsIndex(visibleAlbumsIndex, increase);
    mainComponent->loadMultipleAlbums(musicFolder, visibleAlbumsIndex);

    selectedAlbumIndex = visibleAlbumsIndex;
    mainComponent->loadSingleAlbum(musicFolder, selectedAlbumIndex);
}

void Gui::handleUserInputNumbers(char number)
{
    if(userInputSongNumber.length() >= 5)
        return;

    userInputSongNumber += number;
    mainComponent->setCurrentUserInputNumber(userInputSongNumber);

    if(userInputSongNumber.length() == 5)
    {
        int albumNumber = std::stoi(userInputSongNumber.substr(0, 3));
        int songNumber = std::stoi(userInputSongNumber.substr(3));
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
    if(secondsToPlayTimer)
    {
        secondsToPlayTimer.reset();
    }

    userInputSongNumber = "";
    mainComponent->setCurrentUserInputNumber(userInputSongNumber);
}

void Gui::playSongWithDelay(int albumNumber, int songNumber)
{
    const auto song = SongBuilder::buildSong(albumNumber, songNumber, musicFolder);
    if(!song.fileName.empty())
    {
        secondsToPlayTimer = std::make_unique<JukeboxTimer>([this, song](){
           playSongSignal(song);
           userInputSongNumber = "";
           mainComponent->setCurrentUserInputNumber(userInputSongNumber);

           secondsToPlayTimer.reset();
        });

        secondsToPlayTimer->startTimer(timeToPlay);
    }
    else
    {
        showStatusMessage(ResourceId::ErrorSongNotExists);

        userInputSongNumber = "";
        mainComponent->setCurrentUserInputNumber(userInputSongNumber);
    }
}

void Gui::playAlbumWithDelay(int albumNumber)
{
    const auto songs = SongBuilder::buildSongsInAlbum(albumNumber, musicFolder);
    if(!songs.empty())
    {
        secondsToPlayTimer = std::make_unique<JukeboxTimer>([this, songs](){
            playAlbumSignal(songs);
            userInputSongNumber = "";
            mainComponent->setCurrentUserInputNumber(userInputSongNumber);

            secondsToPlayTimer.reset();
        });

        secondsToPlayTimer->startTimer(timeToPlay);
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
    mainComponent->loadSingleAlbum(musicFolder, selectedAlbumIndex);

    if((increase && selectedAlbumIndex >= visibleAlbumsIndex + albumIndexStep) ||
       (!increase && selectedAlbumIndex < visibleAlbumsIndex))
    {
        visibleAlbumsIndex = getNextVisibleAlbumsIndex(visibleAlbumsIndex, increase);
        mainComponent->loadMultipleAlbums(musicFolder, visibleAlbumsIndex);
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
