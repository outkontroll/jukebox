#ifndef FILESYSTEM_H_INCLUDED
#define FILESYSTEM_H_INCLUDED

#include <vector>
#include <string>

namespace jukebox { namespace filesystem {
  
class FileSystem
{
public:
    static std::string getPicturePath(const std::string& musicDirectory, unsigned int albumIndex, const std::string& pictureExtensions);

    static std::string getInfoFilePath(const std::string& musicDirectory, unsigned int albumIndex);

    static std::string getSongFilePath(const std::string& musicDirectory, unsigned int albumIndex, unsigned int songIndex, const std::string& extensionPattern);

    static std::vector<std::pair<std::string, int>> getAllSongFilesWithFullPaths(const std::string& musicDicertory, unsigned int albumIndex, const std::string& extensionPattern);

    static std::vector<std::string> getAllSongFilesNamesOnly(const std::string& musicDirectory, unsigned int albumIndex, const std::string& extensionPattern);
};

}}


#endif  // FILESYSTEM_H_INCLUDED
