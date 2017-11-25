#ifndef FILESYSTEM_H_INCLUDED
#define FILESYSTEM_H_INCLUDED

#include "IFileSystem.h"

namespace jukebox { namespace filesystem {
  
class FileSystem : public IFileSystem
{
public:
    ~FileSystem() override = default;

    std::string getPicturePath(const std::string& musicDirectory, int albumIndex, const std::string& pictureExtensions) const override;
    std::string getInfoFilePath(const std::string& musicDirectory, int albumIndex) const override;
    std::string getSongFilePath(const std::string& musicDirectory, int albumIndex, int songIndex, const std::string& extensionPattern) const override;
    std::vector<std::pair<std::string, int>> getAllSongFilesWithFullPaths(const std::string& musicDicertory, int albumIndex, const std::string& extensionPattern) const override;
    std::vector<std::string> getAllSongFilesNamesOnly(const std::string& musicDirectory, int albumIndex, const std::string& extensionPattern) const override;
};

}}


#endif  // FILESYSTEM_H_INCLUDED
