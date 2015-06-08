/*
  ==============================================================================

    Application.cpp
    Created: 14 Mar 2015 3:34:51am
    Author:  adam

  ==============================================================================
*/

#include "Application.h"
#include "Core.h"
#include "Logger.h"

using namespace jukebox;
using namespace juce;

jukeboxApplication::jukeboxApplication()
 : core(new core::Core)
{
    LOG_INITIALIZE("jukebox.log");
    LOG_INFO("Application started");
}

jukeboxApplication::~jukeboxApplication()
{
    LOG_INFO("Application stopped");
}
    
const String jukeboxApplication::getApplicationName()
{
    return ProjectInfo::projectName;
}
    
const String jukeboxApplication::getApplicationVersion()
{
    return ProjectInfo::versionString;
}
    
bool jukeboxApplication::moreThanOneInstanceAllowed()
{
    return false;
}
    
void jukeboxApplication::initialise (const String& commandLine)
{
    core->initialize(getApplicationName().toStdString());
}
    
void jukeboxApplication::shutdown()
{
    core->uninitialize();
    core = nullptr;
}
    
void jukeboxApplication::systemRequestedQuit()
{
    LOG_WARNING("unusual terminating");
    quit();
}
    
void jukeboxApplication::anotherInstanceStarted(const String& commandLine)
{
    LOG_ERROR("unexpected second start, exiting");
    quit();
}
