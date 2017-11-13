#include "FileSystem.h"
#include "Formaters.h"
#include "Logger.h"
#include "JuceHeader.h"
#include <algorithm>
#include <utility>
#include <tuple>

using namespace jukebox::filesystem;
using namespace juce;

template<typename ReturnType, bool ReturnAllElements>
ReturnType getFilePathInAlbum(const std::string& musicDirectory, const String& albumDir, const std::string& wildCardPattern);

template<typename ReturnType, bool ReturnAllElements>
ReturnType getAllFileInAlbum(const std::string& musicDirectory, const String& albumDir, const std::string& wildCardPattern);

std::string FileSystem::getPicturePath(const std::string& musicDirectory, int albumIndex, const std::string& pictureExtensions)
{
    std::string wildCardPattern("*" + pictureExtensions);
    return getFilePathInAlbum<std::string, false>(musicDirectory, FillWithLeadingZeros(albumIndex, 3), wildCardPattern);
}

std::string FileSystem::getInfoFilePath(const std::string& musicDirectory, int albumIndex)
{
    return getFilePathInAlbum<std::string, false>(musicDirectory, FillWithLeadingZeros(albumIndex, 3), "*.txt");
}

std::string FileSystem::getSongFilePath(const std::string& musicDirectory, int albumIndex, int songIndex, const std::string& extensionPattern)
{
    //TODO iterate through all the patterns and include the song number in front of the asterisk
    std::string wildCardPattern(FillWithLeadingZeros(songIndex, 2) + extensionPattern);
    return getFilePathInAlbum<std::string, false>(musicDirectory, FillWithLeadingZeros(albumIndex, 3), wildCardPattern);
}

std::vector<std::pair<std::string, int>> FileSystem::getAllSongFilesWithFullPaths(const std::string& musicDicertory, int albumIndex, const std::string& extensionPattern)
{
    //TODO iterate through all the patterns
    const auto files = getAllFileInAlbum<Array<File>, true>(musicDicertory, FillWithLeadingZeros(albumIndex, 3), extensionPattern);

    std::vector<std::pair<std::string, int>> paths;
    paths.reserve(files.size());

    std::transform(files.begin(), files.end(), std::back_inserter(paths), [](const File& file){
        const auto filePath = file.getFullPathName().toStdString();
        const int index = [&](){
            try
            {
                return std::stoi(file.getFileNameWithoutExtension().substring(0, 2).toStdString());
            }
            catch(std::exception e)
            {
                LOG_ERROR(e.what());
                return -1;
            }
        }();

        return std::make_pair(filePath, index);
    });

    std::sort(paths.begin(), paths.end(), [](const auto& lhs, const auto& rhs){
        return std::tie(lhs.first, lhs.second) < std::tie(rhs.first, rhs.second);
    });

    return paths;
}

std::vector<std::string> FileSystem::getAllSongFilesNamesOnly(const std::string& musicDirectory, int albumIndex, const std::string& extensionPattern)
{
    //TODO iterate through all the patterns
    const auto files = getAllFileInAlbum<Array<File>, true>(musicDirectory, FillWithLeadingZeros(albumIndex, 3), extensionPattern);

    std::vector<std::string> musicSongs;
    musicSongs.reserve(files.size());

    std::transform(files.begin(), files.end(), std::back_inserter(musicSongs), [](const File& file){
        return file.getFileNameWithoutExtension().toStdString();
    });

    return musicSongs;
}

template<typename ReturnType, bool ReturnAllElements>
ReturnType getFilePathInAlbum(const std::string& musicDirectory, const String& albumDir, const std::string& wildCardPattern)
{
    File musicDir(musicDirectory);
    if(!musicDir.isDirectory())
    {
        LOG_ERROR("Non-existent directory: " << musicDirectory);
        return "";
    }

    File albumDirectory = musicDir.getChildFile(albumDir);
    if(!albumDirectory.isDirectory())
    {
        LOG_ERROR("Non-existent directory: " << albumDirectory.getFileName());
        return "";
    }

    Array<File> results;
    if(albumDirectory.findChildFiles(results, File::TypesOfFileToFind::findFiles, false, wildCardPattern) <= 0)
    {
        LOG_WARNING("Could not find any file with pattern \"" << wildCardPattern << "\" in the album " << albumDirectory.getFullPathName());
        return "";
    }

//    if constexpr(ReturnAllElements)
//    {
//        return results;
//    }
//    else
//    {
    return results[0].getFullPathName().toStdString();
//    }
}

template<typename ReturnType, bool ReturnAllElements>
ReturnType getAllFileInAlbum(const std::string& musicDirectory, const String& albumDir, const std::string& wildCardPattern)
{
    File musicDir(musicDirectory);
    if(!musicDir.isDirectory())
    {
        LOG_ERROR("Non-existent directory: " << musicDirectory);
        return {};
    }

    File albumDirectory = musicDir.getChildFile(albumDir);
    if(!albumDirectory.isDirectory())
    {
        LOG_ERROR("Non-existent directory: " << albumDirectory.getFileName());
        return {};
    }

    Array<File> results;
    if(albumDirectory.findChildFiles(results, File::TypesOfFileToFind::findFiles, false, wildCardPattern) <= 0)
    {
        LOG_WARNING("Could not find any file with pattern \"" << wildCardPattern << "\" in the album " << albumDirectory.getFullPathName());
        return {};
    }

    return results;
}
