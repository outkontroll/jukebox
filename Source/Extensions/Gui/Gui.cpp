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
#include "Password.h"

using namespace jukebox;
using namespace jukebox::gui;
using namespace jukebox::signals;
using namespace jukebox::audio;
using namespace jukebox::songbuilder;
using namespace juce;

namespace {
    constexpr auto defaultAlbumIndex = 1;
    constexpr auto defaultSongIndex = 0;
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
    eventsSlot.connect(this, &Gui::timeToPlayAdvertiseMusicChanged, mainComponent->timeToPlayAdvertiseMusicChangedSignal);
    eventsSlot.connect(this, &Gui::passwordChanged, mainComponent->passwordChangedSignal);
    eventsSlot.connect(this, &Gui::passwordTurnedOff, mainComponent->passwordTurnedOffSignal);
    eventsSlot.connect(this, &Gui::albumImportRequested, mainComponent->requestToImportAlbumSignal);
}

void Gui::keyPressed(const KeyPress& key)
{
    const auto keyCode = key.getKeyCode();
    const auto textCharacter = key.getTextCharacter();

    LOG_INFO("***USER*** " << key.getTextDescription() << ", keyCode: " << keyCode << ", textCharacter: " << textCharacter);

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
        switchBetweenViews();
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

void Gui::refreshCredits(int credits)
{
    mainComponent->refreshCredits(credits);
}

void Gui::showStatusMessage(ResourceId messageId)
{
    mainComponent->showStatusMessage(Resources::getResourceStringFromId(messageId));
}

void Gui::showInsertedAll(int insertedCoins)
{
    mainComponent->showInsertedAll(insertedCoins);
}

void Gui::showInsertedSinceLastSave(int insertedCoins)
{
    mainComponent->showInsertedSinceLastSave(insertedCoins);
}

void Gui::showStatistics(const std::string& statistics)
{
    mainComponent->showStatistics(statistics);
}

void Gui::setFileSystem(filesystem::IFileSystem* filesys)
{
    assert(filesys != nullptr);
    fileSys = filesys;
    mainComponent->setAlbumsForMusicSetup(fileSys->getAlbums());
}

void Gui::refreshAlbums()
{
    mainComponent->setAlbumsForMusicSetup(fileSys->getAlbums());
}

void Gui::loadMultipleAlbums()
{
    mainComponent->loadMultipleAlbums(fileSys->getAlbums(), visibleAlbumsId);
}

void Gui::loadSingleAlbum()
{
    mainComponent->loadSingleAlbum(fileSys->getAlbums(), selectedAlbumId);
}

void Gui::stopAdvertiseMusic()
{
    advertiseMusicPlaying = false;
    removePlayedSongSignal();
}

void Gui::setMusicFolder(const std::string& folder)
{
    visibleAlbumsId = defaultAlbumIndex;
    selectedAlbumId = defaultAlbumIndex;
    selectedSongIndex = defaultSongIndex;

    loadMultipleAlbums();
    loadSingleAlbum();

    mainComponent->updateAlbumSelection(selectedAlbumId);
    mainComponent->updateSongSelection(selectedSongIndex);
    mainComponent->setMusicDirectory(folder);
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

void Gui::setTimeToPlayAdvertiseMusic(int millisecs)
{
    if(millisecs > 0)
        startAdvertiseMusicTimer(millisecs);

    mainComponent->setTimeToPlayAdvertiseMusic(millisecs);
}

void Gui::startAdvertiseMusicTimer(int millisecs)
{
    if(playAdvertiseMusicTimer == nullptr)
    {
        playAdvertiseMusicTimer = std::make_unique<JukeboxTimer>([this](){
            advertiseMusicPlaying = true;
            playAdvertiseMusicSignal();
        });
    }

    playAdvertiseMusicTimer->startTimer(millisecs);
}

void Gui::turnOffAdvertiseMusic()
{
    playAdvertiseMusicTimer.reset();
}

void Gui::setPassword(const Password* password)
{
    mainComponent->setPassword(password);
}

void Gui::turnOffPassword()
{
    mainComponent->turnOffPassword();
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

void Gui::switchBetweenViews()
{
    if(isInUserMode)
    {
        isInMultipleAlbumsMode = !isInMultipleAlbumsMode;
        mainComponent->switchBetweenAlbumViews();
    }
    else
    {
        isInMusicSetupMode = !isInMusicSetupMode;
        mainComponent->switchBetweenAdministratorViews();
    }
}

void Gui::switchBetweenUserModes()
{
    if(isInUserMode)
    {
        if(!mainComponent->showPasswordQuestion())
        {
            return;
        }
    }

    isInUserMode = !isInUserMode;
    mainComponent->switchBetweenUserModes();

    if(isInUserMode && !isInMultipleAlbumsMode)
    {
        mainComponent->switchBetweenAlbumViews();
    }
    else if(!isInUserMode && !isInMusicSetupMode)
    {
        mainComponent->switchBetweenAdministratorViews();
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
    selectedAlbumId = AlbumStepCalculator{static_cast<int>(fileSys->getAlbums().size()), albumIndexStep}.getNextSelectedAlbumIdOnSamePage(visibleAlbumsId, selectedAlbumId);
    selectedSongIndex = defaultSongIndex;

    loadSingleAlbum();

    mainComponent->updateAlbumSelection(selectedAlbumId);
    mainComponent->updateSongSelection(selectedSongIndex);
}

void Gui::stepSelectionSingleAlbumMode()
{
    if(fileSys->getAlbums().empty())
        return;

    selectedSongIndex = SongStepCalculator{}.getNextSelectedSongIndex(static_cast<int>(fileSys->getAlbums()[static_cast<size_t>(selectedAlbumId - 1)].songs.size()), selectedSongIndex);

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
    visibleAlbumsId = AlbumStepCalculator{static_cast<int>(fileSys->getAlbums().size()), albumIndexStep}.getNextVisibleAlbumsId(visibleAlbumsId, increase);
    loadMultipleAlbums();

    selectedAlbumId = visibleAlbumsId;
    loadSingleAlbum();
}

void Gui::handleUserInputNumbers(char number)
{
    if(advertiseMusicPlaying)
    {
        stopAdvertiseMusic();
    }

    if(userInputSongNumber.length() >= 5)
        return;

    userInputSongNumber += number;
    mainComponent->setCurrentUserInputNumber(userInputSongNumber);

    if(userInputSongNumber.length() == 5)
    {
        const auto albumNumber = std::stoi(userInputSongNumber.substr(0, 3));
        const auto songNumber = std::stoi(userInputSongNumber.substr(3));
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
    timeToPlayASongChangedSignal(std::move(millisecs));
}

void Gui::timeToSaveInsertedCoinsChanged(int millisecs)
{
    timeToSaveInsertedCoinsChangedSignal(std::move(millisecs));
}

void Gui::timeToPlayAdvertiseMusicChanged(int millisecs)
{
    timeToPlayAdvertiseMusicChangedSignal(std::move(millisecs));
}

void Gui::passwordChanged(const Password& password_)
{
    passwordChangedSignal(password_);
}

void Gui::passwordTurnedOff()
{
    passwordTurnedOffSignal();
}

void Gui::albumImportRequested(const std::string& albumToImport)
{
    requestToImportAlbumSignal(albumToImport);
}

void Gui::playSongWithDelay(int albumNumber, int songNumber)
{
    const int albumIndex = albumNumber - 1;
    const int songIndex = songNumber - 1;
    const auto& albums = fileSys->getAlbums();
    if(static_cast<size_t>(albumIndex) >= albums.size() ||
       static_cast<size_t>(songIndex) >= albums[static_cast<size_t>(albumIndex)].songs.size())
    {
        showStatusMessage(ResourceId::ErrorSongNotExists);

        userInputSongNumber = "";
        mainComponent->setCurrentUserInputNumber(userInputSongNumber);

        return;
    }

    const auto& song = albums[static_cast<size_t>(albumIndex)].songs[static_cast<size_t>(songIndex)];

    secondsToPlayTimer = std::make_unique<JukeboxTimer>([this, song](){
        playSongSignal(song);
        userInputSongNumber = "";
        mainComponent->setCurrentUserInputNumber(userInputSongNumber);

        secondsToPlayTimer.reset();
    });

    secondsToPlayTimer->startTimer(timeToPlaySong);

}

void Gui::playAlbumWithDelay(int albumNumber)
{
    const int albumIndex = albumNumber - 1;
    const auto& albums = fileSys->getAlbums();
    if(static_cast<size_t>(albumIndex) >= albums.size())
    {
        showStatusMessage(ResourceId::ErrorAlbumNotExists);

        userInputSongNumber = "";
        mainComponent->setCurrentUserInputNumber(userInputSongNumber);

        return;
    }

    if(albums[static_cast<size_t>(albumIndex)].songs.empty())
    {
        showStatusMessage(ResourceId::ErrorAlbumEmpty);

        userInputSongNumber = "";
        mainComponent->setCurrentUserInputNumber(userInputSongNumber);

        return;
    }

    const auto album = SongBuilder::buildAlbum(albumIndex + 1);
    const auto& songs = albums[static_cast<size_t>(albumIndex)].songs;

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
    const AlbumStepCalculator calc{static_cast<int>(fileSys->getAlbums().size()), albumIndexStep};
    selectedAlbumId = calc.getNextSelectedAlbumId(selectedAlbumId, increase);
    loadSingleAlbum();

    if(calc.shouldStepVisibleAlbums(visibleAlbumsId, selectedAlbumId, increase))
    {
        visibleAlbumsId = calc.getNextVisibleAlbumsId(visibleAlbumsId, increase);
        loadMultipleAlbums();
    }
}
