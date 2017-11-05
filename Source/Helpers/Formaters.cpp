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
