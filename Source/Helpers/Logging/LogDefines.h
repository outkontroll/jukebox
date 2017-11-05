#ifndef LOGDEFINES_H_INCLUDED
#define LOGDEFINES_H_INCLUDED

#include <string>
#include <sstream>
#include <iomanip>
#include "Times.h"

namespace jukebox { namespace log {

#ifdef __GNUC__

  const unsigned short colonSize = 2;

  inline std::string methodName(const std::string& functionName)
  {
      const size_t firstParenthesis = functionName.find("(");
      const size_t lastColons = functionName.rfind("::", firstParenthesis);
    
      if(lastColons == std::string::npos)
      {
          //basic functions: void f()
          const size_t begin = functionName.rfind(" ") + 1;
          const size_t end = firstParenthesis - begin;

          return functionName.substr(begin, end);
      }
      else
      {
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

          const size_t end = firstParenthesis - classNameBegin;
          return functionName.substr(classNameBegin, end);
      }

      return "";
  }

  #define METHOD_NAME jukebox::log::methodName(__PRETTY_FUNCTION__)

#else

  #define METHOD_NAME __FUNCTION__

#endif

// Helper function to right-sided trim a string to a given max length
inline std::string GetTrimmedString(const std::string& what, unsigned int maxLength)
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
                                                    ss << METHOD_NAME << ": " << logText;               \
                                                    logger.log(ss.str());                               \
                                                }

#define LOG_INFO_DETAILED(logger, logText) LOG_DETAILED(logger, "LOG_INFO\t", logText)
#define LOG_WARNING_DETAILED(logger, logText) LOG_DETAILED(logger, "LOG_WARNING\t", logText)
#define LOG_ERROR_DETAILED(logger, logText) LOG_DETAILED(logger, "LOG_ERROR\t", logText)

}}
                                                
#endif  // LOGDEFINES_H_INCLUDED
