#ifndef FILESYSTEM_H_INCLUDED
#define FILESYSTEM_H_INCLUDED

#include <vector>
#include <string>
#include "JuceHeader.h"

namespace jukebox { namespace filesystem {
  
class FileSystem
{
public:
    static std::string getPicturePath(const std::string& musicDirectory, int albumIndex, const std::string& pictureExtensions);

    static std::string getInfoFilePath(const std::string& musicDirectory, int albumIndex);

    static std::string getSongFilePath(const std::string& musicDirectory, const juce::String& albumDir, const std::string& songNum, const std::string& extensionPattern);
};

}}


#endif  // FILESYSTEM_H_INCLUDED
