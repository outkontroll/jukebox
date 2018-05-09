#include "Application.h"
#include "Core.h"
#include "Gui.h"
#include "CreditManager.h"
#include "MusicPlayer.h"
#include "Statistics.h"
#include "Settings.h"
#include "FileSystem.h"
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
    
void jukeboxApplication::initialise(const juce::String& commandLine)
{
    core = std::make_unique<core::Core>(std::make_unique<gui::Gui>(getApplicationName().toStdString()),
                                        std::make_unique<creditmanager::CreditManager>(),
                                        std::make_unique<audio::MusicPlayer>(),
                                        std::make_unique<statistics::Statistics>(),
                                        std::make_unique<settings::Settings>(juce::File::getCurrentWorkingDirectory().getFullPathName().toStdString()),
                                        std::make_unique<filesystem::FileSystem>());

    eventsSlot.connect(this, &jukeboxApplication::exitRequested, core->exitRequestedSignal);
    
    LOG_INFO("Command line: " << commandLine);
    LOG_INFO("done");
}

void jukeboxApplication::shutdown()
{
    core = nullptr;
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
