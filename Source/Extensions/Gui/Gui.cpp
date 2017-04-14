#include "Gui.h"
#include "MainWindow.h"
#include "MainComponent.h"
#include "FileSystem.h"
#include "Logger.h"
#include <algorithm>

using namespace jukebox::gui;
using namespace jukebox::signals;
using namespace jukebox::audio;
using namespace jukebox::filesystem;
using namespace juce;

const std::string INVALID_STRING = "";
const unsigned int INVALID_POSITION = 0;
const unsigned int FIRST_POSITION = 1;

Gui::Gui()
: musicFolder(INVALID_STRING),
  position(INVALID_POSITION)
{
}

Gui::~Gui()
{
}

void Gui::initialize(const std::string& name)
{
    mainComponent.reset(new MainComponent);
    keyPressedSlot.connect(this, &Gui::keyPressed, mainComponent->keyPressedSignal);
    mainWindow.reset(new MainWindow(name, mainComponent.get()));
    
    LOG_INFO("done");
}

void Gui::uninitialize()
{
    mainWindow = nullptr;
    mainComponent = nullptr;
    
    LOG_INFO("done");
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
        playSongSignal(Song(1, 5));
    }
    else if(keyChar == 'v')
    {
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
    position = FIRST_POSITION;
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

void Gui::enqueue(const std::string& song)
{
    mainComponent->enqueue(song);
}

void Gui::removeNextSong()
{
    mainComponent->removeNextSong();
}
