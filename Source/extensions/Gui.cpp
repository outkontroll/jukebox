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
#include "CreditManager.h"

Gui::Gui()
{
}

Gui::~Gui()
{
}

void Gui::initialise(const String& name)
{
    mainComponent.reset(new MainComponent);
    creditManager.reset(new CreditManager);
    mainComponent->setCreditManager(creditManager);
    mainWindow.reset(new MainWindow(name, mainComponent.get()));
}

void Gui::uninitialise()
{
    mainWindow = nullptr;
    mainComponent = nullptr;
    creditManager = nullptr;
}
