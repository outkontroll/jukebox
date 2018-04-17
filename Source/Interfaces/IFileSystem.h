#ifndef IFILESYSTEM_H
#define IFILESYSTEM_H

#include <string>
#include <vector>

namespace jukebox { namespace filesystem {

class IFileSystem
{
public:
    virtual ~IFileSystem() = default;

    virtual std::string getPicturePath(const std::string& musicDirectory, unsigned int albumIndex, const std::string& pictureExtensions) const = 0;
    virtual std::string getInfoFilePath(const std::string& musicDirectory, unsigned int albumIndex) const = 0;
    virtual std::string getSongFilePath(const std::string& musicDirectory, unsigned int albumIndex, unsigned int songIndex, const std::string& extensionPattern) const = 0;
    virtual std::vector<std::pair<std::string, unsigned int>> getAllSongFilesWithFullPaths(const std::string& musicDicertory, unsigned int albumIndex, const std::string& extensionPattern) const = 0;
    virtual std::vector<std::string> getAllSongFilesNamesOnly(const std::string& musicDirectory, unsigned int albumIndex, const std::string& extensionPattern) const = 0;
};

}}

#endif //IFILESYSTEM_H
