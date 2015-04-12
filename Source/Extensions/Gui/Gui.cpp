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

using namespace jukebox::gui;
using namespace jukebox::signals;

Gui::Gui()
{
}

Gui::~Gui()
{
}

void Gui::initialise(const String& name)
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
        playSongSignal();
    }
    else if(keyChar == 'v')
    {
        playAlbumSignal();
    }
}

void Gui::refreshCredits(unsigned int credits)
{
    mainComponent->refreshCredits(credits);
}

void Gui::showStatusMessage(const String& message)
{
    mainComponent->showStatusMessage(message);
}
