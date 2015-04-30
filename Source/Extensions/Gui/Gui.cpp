/*
  ==============================================================================

    Gui.cpp
    Created: 15 Mar 2015 1:55:03pm
    Author:  adam

  ==============================================================================
*/

#include "Gui.h"
#include "MainWindow.h"
#include "MainComponent.h"
#include "FileSystem.h"
#include <algorithm>

using namespace jukebox::gui;
using namespace jukebox::signals;
using namespace jukebox::audio;
using namespace jukebox::filesystem;

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

void Gui::initialise(const std::string& name)
{
    mainComponent.reset(new MainComponent);
    keyPressedSlot.connect(this, &Gui::keyPressed, mainComponent->keyPressedSignal);
    mainWindow.reset(new MainWindow(name, mainComponent.get()));
}

void Gui::uninitialise()
{
    mainWindow = nullptr;
    mainComponent = nullptr;
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
        playSongSignal(Song());
    }
    else if(keyChar == 'v')
    {
        playAlbumSignal(Song(12));
    }
    else if(keyCode == KeyPress::escapeKey)
    {
        showStatisticsSignal();
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
    FileSystem::T_AlbumDirectories albumDirs = FileSystem::getAlbumDirectories(".");
    
    for(auto i : albumDirs)
    {
        albumlist += i + "\n";
    }
    
    mainComponent->updateAlbumList(albumlist);
}
