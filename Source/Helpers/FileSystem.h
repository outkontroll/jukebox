/*
  ==============================================================================

    FileSystem.h
    Created: 20 Apr 2015 12:31:19am
    Author:  adam

  ==============================================================================
*/

#ifndef FILESYSTEM_H_INCLUDED
#define FILESYSTEM_H_INCLUDED

#include <vector>
#include <string>

namespace jukebox { namespace filesystem {
  
class FileSystem
{
public:
    typedef std::vector<std::string> T_AlbumDirectories;
    static T_AlbumDirectories getAlbumDirectories(const std::string& path);
    
    typedef std::vector<std::string> T_SongFiles;
    static T_SongFiles getSongFiles(const std::string& path, const std::string& extensions = "*.wav");
};

}}


#endif  // FILESYSTEM_H_INCLUDED
