#include "Gui.h"
#include "MainWindow.h"
#include "MainComponent.h"
#include "FileSystem.h"
#include "Logger.h"
#include <iterator>
#include <algorithm>
#include <numeric>
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
    else if(textCharacter == 'x')
    {
        static int fileToPlay = 0;
        ++fileToPlay;
        fileToPlay = fileToPlay % 3;
        //TODO
        playSongSignal(Song(7, filesToPlay[fileToPlay]));
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

void Gui::enqueue(const audio::Song& song)
{
    mainComponent->enqueue(song);
}

void Gui::removeNextSong()
{
    mainComponent->removeNextSong();
}

void Gui::updateAlbumList()
{
    const auto directories(FileSystem::getAlbumDirectories("."));
    mainComponent->updateAlbumList(std::accumulate(std::begin(directories),
                                                   std::end(directories),
                                                   std::string(),
                                                   [](const std::string& init, const std::string& directory) {
                                                       return init + "\n" + directory;
    }));
}

void Gui::showHelp()
{

}
