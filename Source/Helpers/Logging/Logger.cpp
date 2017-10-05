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
:   logFileName(""),
    enabled(true)
{
}

void Logger::setLogFileName(const std::string& fileName)
{
    logFileName = fileName;
}

jukebox::ScopeGuard<bool> Logger::disableLog()
{
    return { enabled, false };
}

void Logger::log(const std::string& logText)
{
    if(enabled)
        //TODO: log into a .log file
        std::cout << logText << std::endl;
}
