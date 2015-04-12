/*
  ==============================================================================

    Core.cpp
    Created: 15 Mar 2015 1:37:31pm
    Author:  adam

  ==============================================================================
*/

#include "Core.h"
#include "Gui.h"

Core::Core()
{
}

Core::~Core()
{
}

void Core::initialise(const String& name)
{
    gui.reset(new Gui);
    gui->initialise(name);
}

void Core::uninitialise()
{
    gui->uninitialise();
    gui = nullptr;
}
