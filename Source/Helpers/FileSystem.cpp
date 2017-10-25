#include "FileSystem.h"
#include "Logger.h"
#include "JuceHeader.h"

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
    
    return albumDirs;
}
    
std::vector<std::string> FileSystem::getSongFiles(const std::string& path, const std::string& /*musicExtensions*/)
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

std::string FileSystem::getPicturePath(const std::string& path, const std::string& pictureExtensions)
{
    if(path == "")
    {
        LOG_WARNING("called with empty path!");
        return {};
    }

    //TODO get actal files, match only one extension
    return path + "/cover" + pictureExtensions;
}
