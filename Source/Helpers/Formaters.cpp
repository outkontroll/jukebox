#include "Formaters.h"
#include <sstream>
#include <iomanip>
#include <cassert>

std::string jukebox::FillWithLeadingZeros(unsigned int number, unsigned int length)
{
    assert(length != 0);
        
    std::stringstream ss;
    ss << std::setw(static_cast<int>(length)) << std::setfill('0') << number;
    
    return ss.str();
}
