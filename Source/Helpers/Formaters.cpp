#include "Formaters.h"
#include "Logger.h"
#include <sstream>
#include <iomanip>

std::string jukebox::FillWithLeadingZeros(unsigned int number, unsigned int length)
{
    if(length == 0)
    {
        LOG_WARNING("called with 0 length!");
        return "";
    }
        
    std::stringstream ss;
    ss << std::setw(static_cast<int>(length)) << std::setfill('0') << number;
    
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
