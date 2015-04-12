/*
  ==============================================================================

    Application.cpp
    Created: 14 Mar 2015 3:34:51am
    Author:  adam

  ==============================================================================
*/

#include "Application.h"
#include "Core.h"

jukeboxApplication::jukeboxApplication()
 : core(new Core)
{
}

jukeboxApplication::~jukeboxApplication()
{
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
    core->initialise(getApplicationName());
}
    
void jukeboxApplication::shutdown()
{
    core->uninitialise();
    core = nullptr;
}
    
void jukeboxApplication::systemRequestedQuit()
{
    std::cout << __func__ << std::endl;
    quit();
}
    
void jukeboxApplication::anotherInstanceStarted(const String& commandLine)
{
    //TODO
}
