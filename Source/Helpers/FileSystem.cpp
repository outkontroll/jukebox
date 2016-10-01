/*
  ==============================================================================

    FileSystem.cpp
    Created: 20 Apr 2015 12:31:19am
    Author:  adam

  ==============================================================================
*/

#include "FileSystem.h"
#include "Logger.h"

using namespace jukebox::filesystem;

FileSystem::T_AlbumDirectories FileSystem::getAlbumDirectories(const std::string& path)
{
    if(path == "")
    {
        LOG_WARNING("called with empty path!");
        return T_AlbumDirectories();
    }
        
    T_AlbumDirectories albumDirs;
    //TODO
    albumDirs.push_back("kamu");
    albumDirs.push_back(std::string("adatok"));
    
    return albumDirs;
}
    
FileSystem::T_SongFiles FileSystem::getSongFiles(const std::string& path, const std::string& /*extensions*/)
{
    if(path == "")
    {
        LOG_WARNING("called with empty path!");
        return T_SongFiles();
    }
    
    //TODO
    return T_SongFiles();
}
