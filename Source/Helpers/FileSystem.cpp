#include "FileSystem.h"
#include "Logger.h"

using namespace jukebox::filesystem;

std::vector<std::string> FileSystem::getAlbumDirectories(const std::string& path)
{
    std::vector<std::string> albumDirs;
    if(path.empty())
    {
        LOG_WARNING("called with empty path!");
        return albumDirs;
    }

    //TODO
    albumDirs.push_back("kamu");
    albumDirs.push_back(std::string("adatok"));
    
    return albumDirs;
}
    
std::vector<std::string> FileSystem::getSongFiles(const std::string& path, const std::string& /*extensions*/)
{
    std::vector<std::string> songFiles;
    if(path == "")
    {
        LOG_WARNING("called with empty path!");
        return songFiles;
    }
    
    //TODO
    return songFiles;
}
