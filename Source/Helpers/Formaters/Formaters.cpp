#include "Formaters.h"
#include <sstream>
#include <iomanip>
#include <cassert>

std::string jukebox::FillWithLeadingZeros(int number, int length)
{
    assert(length > 0);
        
    std::stringstream ss;
    ss << std::setw(length) << std::setfill('0') << number;
    
    return ss.str();
}
