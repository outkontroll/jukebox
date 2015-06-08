/*
  ==============================================================================

    Logger.h
    Created: 6 Jun 2015 8:19:02pm
    Author:  adam

  ==============================================================================
*/

#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <string>
#include "LogDefines.h"

namespace jukebox { namespace log {

class Logger
{
    public:
        static Logger& getInstance();
        
        void setLogFileName(const std::string& fileName);
        void log(const std::string& logText);
        
    private:
        Logger();
        
    private:
        std::string logFileName;
};

#define LOG_INFO(logText) LOG_INFO_DETAILED(jukebox::log::Logger::getInstance(), logText);
#define LOG_WARNING(logText) LOG_WARNING_DETAILED(jukebox::log::Logger::getInstance(), logText);
#define LOG_ERROR(logText) LOG_ERROR_DETAILED(jukebox::log::Logger::getInstance(), logText);

#define LOG_INITIALIZE(fileName) jukebox::log::Logger::getInstance().setLogFileName(fileName)

}}



#endif  // LOGGER_H_INCLUDED
