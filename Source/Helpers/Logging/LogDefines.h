/*
  ==============================================================================

    LogDefines.h
    Created: 7 Jun 2015 10:03:08am
    Author:  adam

  ==============================================================================
*/

#ifndef LOGDEFINES_H_INCLUDED
#define LOGDEFINES_H_INCLUDED

#include <string>
#include <sstream>
#include <iomanip>
#include "Times.h"

namespace jukebox { namespace log {

#ifdef __GNUC__

  const unsigned short colonSize = 2;

  inline const std::string methodName(const std::string& functionName)
  {
      size_t firstParenthesis = functionName.find("(");
      size_t lastColons = functionName.rfind("::", firstParenthesis);
    
      if(lastColons == std::string::npos)
      {
          //basic functions: void f()
          size_t begin = functionName.rfind(" ") + 1;
          size_t end = firstParenthesis - begin;

          return functionName.substr(begin, end);
      }
      else
      {
          size_t end = std::string::npos;
          size_t classNameBegin = functionName.rfind("::", lastColons - 1);
          
          if(classNameBegin == std::string::npos)
          {
              //functions in single class or namespace: void A::f()
              classNameBegin = functionName.substr(0, lastColons).rfind(" ") + 1;
          }
          else
          {
              //functions in multiple namespaces and/or classes: void A::B::f()
              classNameBegin += colonSize;
          }

          end = firstParenthesis - classNameBegin;
          return functionName.substr(classNameBegin, end);
      }

      return "";
  }

  #define __METHOD_NAME__ jukebox::log::methodName(__PRETTY_FUNCTION__)

#else

  #define __METHOD_NAME__ __FUNCTION__

#endif

// Helper function to trim a string to a given max length from the rigth side
inline const std::string GetTrimmedString(const std::string& what, unsigned int maxLength)
{
    if(maxLength >= what.length())
    {
        return what;
    }
    
    return what.substr(what.length() - maxLength - 1);
}

#define LOG_DETAILED(logger, logType, logText)  {                                                       \
                                                    std::stringstream ss;                               \
                                                    ss << logType << "\t";                              \
                                                    ss << jukebox::CurrentDateTime() << "\t";           \
                                                    ss << std::setw(41);                                \
                                                    ss << jukebox::log::GetTrimmedString(__FILE__, 40); \
                                                    ss << ": line #" << __LINE__ << "\t";               \
                                                    ss << __METHOD_NAME__ << ": " << logText;           \
                                                    logger.log(ss.str());                               \
                                                }

#define LOG_INFO_DETAILED(logger, logText) LOG_DETAILED(logger, "LOG_INFO", logText)
#define LOG_WARNING_DETAILED(logger, logText) LOG_DETAILED(logger, "LOG_WARNING", logText)
#define LOG_ERROR_DETAILED(logger, logText) LOG_DETAILED(logger, "LOG_ERROR", logText)

}}
                                                
#endif  // LOGDEFINES_H_INCLUDED