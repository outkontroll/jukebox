/*
  ==============================================================================

    Core.cpp
    Created: 15 Mar 2015 1:37:31pm
    Author:  adam

  ==============================================================================
*/

#include "Core.h"
#include "Gui.h"
#include "CreditManager.h"

using namespace jukebox::core;
using namespace jukebox::gui;
using namespace jukebox::signals;

Core::Core()
: number(0)
{
}

Core::~Core()
{
}

void Core::initialise(const String& name)
{
    gui.reset(new gui::Gui);
    eventsSlot.connect(this, &Core::coinInserted50, gui->coinInserted50Signal);
    eventsSlot.connect(this, &Core::coinInserted100, gui->coinInserted100Signal);
    eventsSlot.connect(this, &Core::coinInserted200, gui->coinInserted200Signal);
    eventsSlot.connect(this, &Core::playingSong, gui->playingSongSignal);
    eventsSlot.connect(this, &Core::playingAlbum, gui->playingAlbumSignal);
    eventsSlot.connect(this, &Core::creditIncrease, gui->creditIncreaseSignal);
    eventsSlot.connect(this, &Core::creditDecrease, gui->creditDecreaseSignal);
    eventsSlot.connect(this, &Core::exitRequested, gui->exitRequestedSignal);
    gui->initialise(name);
    
    creditManager.reset(new creditmanager::CreditManager);
}

void Core::uninitialise()
{
    gui->uninitialise();
    gui = nullptr;
    
    creditManager = nullptr;
}

void Core::coinInserted50()
{
    creditManager->coinInsert50();
    gui->refreshCredits(creditManager->getCredits());
}

void Core::coinInserted100()
{
    creditManager->coinInsert100();
    gui->refreshCredits(creditManager->getCredits());
}

void Core::coinInserted200()
{
    creditManager->coinInsert200();
    gui->refreshCredits(creditManager->getCredits());
}
    
void Core::playingSong()
{
    if(! creditManager->hasEnoughCreditsToPlaySong())
    {
        gui->showStatusMessage("Too few credits to play a song!");
    }
    else
    {
        creditManager->startPlaySong();
        gui->refreshCredits(creditManager->getCredits());
    }
}

void Core::playingAlbum()
{
    if(! creditManager->hasEnoughCreditsToPlayAlbum())
    {
        gui->showStatusMessage("Too few credits to play an album!");
    }
    else
    {
        creditManager->startPlayAlbum();
        gui->refreshCredits(creditManager->getCredits());
    }
}
    
void Core::creditIncrease()
{
    creditManager->creditIncrease();
    gui->refreshCredits(creditManager->getCredits());
}

void Core::creditDecrease()
{
    creditManager->creditDecrease();
    gui->refreshCredits(creditManager->getCredits());
}
    
void Core::exitRequested()
{
    JUCEApplication::quit();
}
