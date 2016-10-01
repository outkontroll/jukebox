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

jukeboxApplication::jukeboxApplication()
{
    LOG_INITIALIZE("jukebox.log");
    LOG_INFO("Application started");
}

jukeboxApplication::~jukeboxApplication()
{
    LOG_INFO("Application stopped");
}
    
const juce::String jukeboxApplication::getApplicationName()
{
    return ProjectInfo::projectName;
}
    
const juce::String jukeboxApplication::getApplicationVersion()
{
    return ProjectInfo::versionString;
}
    
bool jukeboxApplication::moreThanOneInstanceAllowed()
{
    return false;
}
    
void jukeboxApplication::initialise (const juce::String& commandLine)
{
    core = std::make_shared<core::Core>();
    gui = std::make_shared<gui::Gui>();
    creditManager = std::make_shared<creditmanager::CreditManager>();
    musicPlayer = std::make_shared<audio::MusicPlayer>();
    statistics = std::make_shared<statistics::Statistics>();
    eventsSlot.connect(this, &jukeboxApplication::exitRequested, core->exitRequestedSignal);
    core->initialize(getApplicationName().toStdString(),
                     gui,
                     creditManager,
                     musicPlayer,
                     statistics);
    
    LOG_INFO("Command line: " << commandLine);
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

void jukeboxApplication::exitRequested()
{
    LOG_INFO("");
    juce::JUCEApplication::quit();
}
    
void jukeboxApplication::anotherInstanceStarted(const juce::String& commandLine)
{
    LOG_ERROR("unexpected second start, exiting");
    LOG_ERROR("Command line: " << commandLine);
    quit();
}
