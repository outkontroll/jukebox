#ifndef FILESYSTEM_H_INCLUDED
#define FILESYSTEM_H_INCLUDED

#include <vector>
#include <string>

namespace jukebox { namespace filesystem {
  
class FileSystem
{
public:
    static std::vector<std::string> getAlbumDirectories(const std::string& path);

    static std::vector<std::string> getSongFiles(const std::string& path, const std::string& extensions = "*.wav");
};

}}


#endif  // FILESYSTEM_H_INCLUDED
