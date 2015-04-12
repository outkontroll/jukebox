/*
  ==============================================================================

    Formaters.cpp
    Created: 12 Apr 2015 3:29:23pm
    Author:  bakos

  ==============================================================================
*/

#include "Formaters.h"
#include <sstream>
#include <iomanip>

using namespace jukebox;

std::string Helper::LeadingZeroConverter(unsigned int number, unsigned int length)
{
    if(! length)
        return "";
        
    std::stringstream ss;
    ss << std::setw(length) << std::setfill('0') << number;
    
    return ss.str();
}
