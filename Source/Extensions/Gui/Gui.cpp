#include "Gui.h"
#include "MainWindow.h"
#include "MainComponent.h"
#include "FileSystem.h"
#include "Logger.h"
#include "Song.h"
#include "ResourceString.h"
#include <algorithm>
#include <numeric>
//TODO remove this as this is just for testing purposes
#include <array>

using namespace jukebox;
using namespace jukebox::gui;
using namespace jukebox::signals;
using namespace jukebox::audio;
using namespace jukebox::filesystem;
using namespace juce;

namespace {
    static const unsigned int defaultAlbumIndex = 1;
    //TODO remove this as this is just for testing purposes
    const std::array<unsigned, 3> filesToPlay = {{ 1, 16, 4 }};
}

Song createSong(unsigned int albumNumber, unsigned int songNumber, const std::string& musicDirectory);

Gui::Gui(const std::string& applicationName)
    : mainComponent(std::make_unique<MainComponent>()),
      mainWindow(std::make_unique<MainWindow>(applicationName, mainComponent.get()))
{
    eventsSlot.connect(this, &Gui::keyPressed, mainComponent->keyPressedSignal);
    eventsSlot.connect(this, &Gui::playNextSong, mainComponent->playNextSongSignal);
}

Gui::~Gui() = default;

void Gui::keyPressed(const KeyPress& key)
{
    const auto keyCode = key.getKeyCode();
    const auto textCharacter = key.getTextCharacter();

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
        handleStepInAllAlbumMode(false);
    }
    else if(textCharacter == '-')
    {
        handleStepInAllAlbumMode(true);
    }
    else if(textCharacter == '0')
    {
        //TODO
    }
    else if(textCharacter == '1')
    {
        //TODO
    }
    else if(textCharacter == '2')
    {
        //TODO
    }
    else if(textCharacter == '3')
    {
        //TODO
    }
    else if(textCharacter == '4')
    {
        //TODO
    }
    else if(textCharacter == '5')
    {
        //TODO
    }
    else if(textCharacter == '6')
    {
        //TODO
    }
    else if(textCharacter == '7')
    {
        //TODO
    }
    else if(textCharacter == '8')
    {
        //TODO
    }
    else if(textCharacter == '9')
    {
        //TODO
    }

    else if(textCharacter == 'a')
    {
        increaseSoundVolumeSignal();
    }
    else if(textCharacter == 's')
    {
        decreaseSoundVolumeSignal();
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
    else if(textCharacter == 'x')
    {
        static int fileToPlay = 0;
        ++fileToPlay;
        fileToPlay = fileToPlay % 3;
        //TODO
        playSongSignal(createSong(7, filesToPlay[fileToPlay], musicFolder));
    }
    else if(textCharacter == 'v')
    {
        //TODO
        playAlbumSignal(Album(12));
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
    mainComponent->loadAlbums(musicFolder, visibleAlbumsIndex);
    mainComponent->loadSingleAlbum(musicFolder, selectedAlbumIndex);
}

void Gui::setCurrentlyPlayedSong(const audio::Song& song)
{
    mainComponent->setCurrentlyPlayedSong(song);
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

void Gui::showHelp()
{

}

void Gui::handleStepInAllAlbumMode(bool increase)
{
    if(isInMultipleAlbumsMode)
        handleStepInMultipleAlbumsMode(increase);
    else
        handleStepInSingleAlbumMode(increase);
}

void Gui::handleStepInMultipleAlbumsMode(bool increase)
{
    visibleAlbumsIndex = getNextVisibleAlbumsIndex(visibleAlbumsIndex, increase);
    mainComponent->loadAlbums(musicFolder, visibleAlbumsIndex);

    selectedAlbumIndex = visibleAlbumsIndex;
    mainComponent->loadSingleAlbum(musicFolder, selectedAlbumIndex);
}

void Gui::handleStepInSingleAlbumMode(bool increase)
{
    selectedAlbumIndex = getNextSelectedAlbumIndex(selectedAlbumIndex, increase);
    mainComponent->loadSingleAlbum(musicFolder, selectedAlbumIndex);

    if((increase && selectedAlbumIndex >= visibleAlbumsIndex + albumIndexStep) ||
       (!increase && selectedAlbumIndex < visibleAlbumsIndex))
    {
        visibleAlbumsIndex = getNextVisibleAlbumsIndex(visibleAlbumsIndex, increase);
        mainComponent->loadAlbums(musicFolder, visibleAlbumsIndex);
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

Song createSong(unsigned int albumNumber, unsigned int songNumber, const std::string& musicDirectory)
{
    //TODO: get the files list and use the one with leading number
    return { Album(albumNumber),
             songNumber,
             std::string(musicDirectory + "/" + FillWithLeadingZeros(albumNumber, 3) + "/" + FillWithLeadingZeros(songNumber, 2) + ".mp3") };
}
