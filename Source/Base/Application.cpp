/*
  ==============================================================================

    Application.cpp
    Created: 14 Mar 2015 3:34:51am
    Author:  adam

  ==============================================================================
*/

#include "Application.h"
#include "Core.h"
//TODO: remove these includes as soon as classload is introduced
#include "Gui.h"
#include "CreditManager.h"
#include "MusicPlayer.h"
#include "Statistics.h"
//ENDTODO
#include "Logger.h"

using namespace jukebox;
using namespace juce;

jukeboxApplication::jukeboxApplication()
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
    core = std::make_shared<core::Core>();
    gui = std::make_shared<gui::Gui>();
    creditManager = std::make_shared<creditmanager::CreditManager>();
    musicPlayer = std::make_shared<audio::MusicPlayer>();
    statistics = std::make_shared<statistics::Statistics>();
    
    core->initialize(getApplicationName().toStdString(),
                     gui,
                     creditManager,
                     musicPlayer,
                     statistics);
    
    LOG_INFO("done");
}
    
void jukeboxApplication::shutdown()
{
    core->uninitialize();
    core = nullptr;
    
    gui = nullptr;
    creditManager = nullptr;
    musicPlayer = nullptr;
    statistics = nullptr;
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
