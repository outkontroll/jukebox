#include "FileSystem.h"
#include "Logger.h"

using namespace jukebox::filesystem;

std::vector<std::string> FileSystem::getAlbumDirectories(const std::string& path)
{
    if(path.empty())
    {
        LOG_WARNING("called with empty path!");
        return {};
    }

    std::vector<std::string> albumDirs;
    //TODO
    albumDirs.push_back(path);
    albumDirs.push_back("kamu");
    albumDirs.push_back(std::string("adatok"));
    
    return albumDirs;
}
    
std::vector<std::string> FileSystem::getSongFiles(const std::string& path, const std::string& /*extensions*/)
{
    if(path == "")
    {
        LOG_WARNING("called with empty path!");
        return {};
    }
    
    std::vector<std::string> songFiles;
    //TODO
    return songFiles;
}
