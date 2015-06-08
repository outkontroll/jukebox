/*
  ==============================================================================

    Formaters.cpp
    Created: 12 Apr 2015 3:29:23pm
    Author:  bakos

  ==============================================================================
*/

#include "Formaters.h"
#include "Logger.h"
#include <sstream>
#include <iomanip>

std::string jukebox::FillWithLeadingZeros(unsigned int number, unsigned int length)
{
    if(! length)
    {
        LOG_WARNING("called with 0 length!");
        return "";
    }
        
    std::stringstream ss;
    ss << std::setw(length) << std::setfill('0') << number;
    
    return ss.str();
}

std::string jukebox::GetTrimmedString(const std::string& what, unsigned int maxLength)
{
    if(maxLength >= what.length())
    {
        return what;
    }
    
    return what.substr(what.length() - maxLength - 1);
}
