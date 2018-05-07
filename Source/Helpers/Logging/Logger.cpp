#include "Logger.h"
#include <fstream>

using namespace jukebox::log;

Logger& Logger::getInstance()
{
    static Logger logger;
    return logger;
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
    {
        std::ofstream f(logFileName.c_str(), std::ios::app);
        if(f)
        {
            f << logText << std::endl;
        }
    }
}
