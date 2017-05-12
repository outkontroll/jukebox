#include "Gui.h"
#include "MainWindow.h"
#include "MainComponent.h"
#include "FileSystem.h"
#include "Logger.h"
#include <algorithm>
//TODO remove this as this is just for testing purposes
#include <array>

using namespace jukebox::gui;
using namespace jukebox::signals;
using namespace jukebox::audio;
using namespace jukebox::filesystem;
using namespace juce;

namespace {
    const std::string InvalidString = "";
    const unsigned int InvalidPosition = 0;
    const unsigned int FirstPosition = 1;

    //TODO remove this as this is just for testing purposes
    const std::array<unsigned, 3> filesToPlay = { 1, 16, 4 };
}

Gui::Gui(const std::string& name)
    : mainComponent(std::make_unique<MainComponent>()),
      mainWindow(std::make_unique<MainWindow>(name, mainComponent.get())),
      musicFolder(InvalidString),
      position(InvalidPosition)
{
    eventsSlot.connect(this, &Gui::keyPressed, mainComponent->keyPressedSignal);
    eventsSlot.connect(this, &Gui::playNextSong, mainComponent->playNextSongSignal);
}

Gui::~Gui()
{
}

void Gui::keyPressed(const KeyPress& key)
{
    int keyCode = key.getKeyCode();
    juce_wchar keyChar = key.getTextCharacter();

    if(keyCode == KeyPress::F4Key)
    {
        exitRequestedSignal();
    }
    else if(keyChar == 'o')
    {
        coinInserted50Signal();
    }
    else if(keyChar == 'p')
    {
        coinInserted100Signal();
    }
    else if(keyChar == 'l')
    {
        coinInserted200Signal();
    }
    else if(keyChar == 'k')
    {
        creditIncreaseSignal();
    }
    else if(keyChar == 'j')
    {
        creditDecreaseSignal();
    }
    else if(keyChar == 'x')
    {
        static int fileToPlay = 0;
        ++fileToPlay;
        fileToPlay = fileToPlay % 3;
        //TODO
        playSongSignal(Song(7, filesToPlay[fileToPlay]));
    }
    else if(keyChar == 'v')
    {
        //TODO
        playAlbumSignal(Album(12));
    }
    else if(keyCode == KeyPress::escapeKey)
    {
        showStatisticsSignal();
    }
    else if(keyCode == KeyPress::backspaceKey)
    {
        removePlayedSongSignal();
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

void Gui::showStatusMessage(const std::string& message)
{
    mainComponent->showStatusMessage(message);
}

void Gui::setMusicFolder(const std::string& folder)
{
    musicFolder = folder;
    position = FirstPosition;
    updateAlbumList();
}

void Gui::updateAlbumList()
{
    std::string albumlist("");
    
    for(auto& i : FileSystem::getAlbumDirectories("."))
    {
        albumlist += i + "\n";
    }
    
    mainComponent->updateAlbumList(albumlist);
}

void Gui::enqueue(const audio::Song& song)
{
    mainComponent->enqueue(song);
}

void Gui::removeNextSong()
{
    mainComponent->removeNextSong();
}
