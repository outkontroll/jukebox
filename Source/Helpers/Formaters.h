#ifndef FORMATERS_H_INCLUDED
#define FORMATERS_H_INCLUDED

#include <string>

namespace jukebox {

    // Helper function to get a right justified string out of a number
    // the remaining places will be filled with zeros
    std::string FillWithLeadingZeros(unsigned int number, unsigned int length);

    // Helper function to trim a string to a given max length from the rigth side
    std::string GetTrimmedString(const std::string& what, unsigned int maxLength);

}



#endif  // FORMATERS_H_INCLUDED
