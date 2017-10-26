#include "FileSystem.h"
#include "Formaters.h"
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

std::string FileSystem::getPicturePath(const std::string& musicDirectory, int albumIndex, const std::string& pictureExtensions)
{
    if(musicDirectory == "")
    {
        LOG_WARNING("called with empty path!");
        return {};
    }

    //TODO get actal files, match only one extension
    return musicDirectory + "/" + FillWithLeadingZeros(albumIndex, 3) + "/cover" + pictureExtensions;
}
