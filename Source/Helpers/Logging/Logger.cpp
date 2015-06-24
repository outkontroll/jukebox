/*
  ==============================================================================

    Logger.cpp
    Created: 6 Jun 2015 8:19:02pm
    Author:  adam

  ==============================================================================
*/

#include "Logger.h"
//TOOD: this is dummy implementation, remove it when logging is done into a file
#include <iostream>

using namespace jukebox::log;

Logger& Logger::getInstance()
{
    static Logger logger;
    return logger;
}

Logger::Logger()
: logFileName("")
{
}

void Logger::setLogFileName(const std::string& fileName)
{
    logFileName = fileName;
}

void Logger::log(const std::string& logText)
{
    //TODO: log into a .log file
    std::cout << logText << std::endl;
}
