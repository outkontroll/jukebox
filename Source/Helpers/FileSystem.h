#ifndef FILESYSTEM_H_INCLUDED
#define FILESYSTEM_H_INCLUDED

#include <vector>
#include <string>

namespace jukebox { namespace filesystem {
  
class FileSystem
{
public:
    using T_AlbumDirectories = std::vector<std::string> ;
    static T_AlbumDirectories getAlbumDirectories(const std::string& path);
    
    using T_SongFiles = std::vector<std::string>;
    static T_SongFiles getSongFiles(const std::string& path, const std::string& extensions = "*.wav");
};

}}


#endif  // FILESYSTEM_H_INCLUDED
