#include "FileSystem.h"
#include <algorithm>
#include <utility>
#include <tuple>
#include <cassert>
#include "StdAddons.hpp"
#include "Formaters.h"
#include "Logger.h"
#include "JuceHeader.h"
#include "Song.h"

using namespace jukebox::filesystem;
using namespace jukebox::audio;
using namespace juce;

namespace {
    const auto musicFilePattern = "??*.mp3"; // exclude 1.mp3 and likes
    const auto infoFilePattern = "*.txt";
    const auto pictureFilePattern = "*.jpg";
}

AlbumInfo loadAlbum(const File& albumDirectory);
std::tuple<std::vector<std::string>, std::string> readInfoFile(const juce::File& albumDirectory);
jukebox::audio::Song createSong(unsigned int albumNumber, unsigned int songNumber, const juce::File& file, std::string_view name);

template<typename ReturnType, bool ReturnAllElements>
ReturnType getFilePathInAlbum(const std::string& musicDirectory, const String& albumDir, const std::string& wildCardPattern);

template<typename ReturnType, bool ReturnAllElements>
ReturnType getAllFileInAlbum(const std::string& musicDirectory, const String& albumDir, const std::string& wildCardPattern);

std::string FileSystem::getPicturePath(const std::string& musicDirectory, unsigned int albumIndex, const std::string& pictureExtensions) const
{
    std::string wildCardPattern("*" + pictureExtensions);
    return getFilePathInAlbum<std::string, false>(musicDirectory, FillWithLeadingZeros(albumIndex, 3), wildCardPattern);
}

std::string FileSystem::getInfoFilePath(const std::string& musicDirectory, unsigned int albumIndex) const
{
    return getFilePathInAlbum<std::string, false>(musicDirectory, FillWithLeadingZeros(albumIndex, 3), "*.txt");
}

std::string FileSystem::getSongFilePath(const std::string& musicDirectory, unsigned int albumIndex, unsigned int songIndex, const std::string& extensionPattern) const
{
    //TODO iterate through all the patterns and include the song number in front of the asterisk
    std::string wildCardPattern(FillWithLeadingZeros(songIndex, 2) + extensionPattern);
    return getFilePathInAlbum<std::string, false>(musicDirectory, FillWithLeadingZeros(albumIndex, 3), wildCardPattern);
}

std::vector<std::pair<std::string, unsigned int>> FileSystem::getAllSongFilesWithFullPaths(const std::string& musicDicertory, unsigned int albumIndex, const std::string& extensionPattern) const
{
    //TODO iterate through all the patterns
    const auto files = getAllFileInAlbum<Array<File>, true>(musicDicertory, FillWithLeadingZeros(albumIndex, 3), extensionPattern);

    std::vector<std::pair<std::string, unsigned int>> paths;
    paths.reserve(static_cast<unsigned int>(files.size()));

    std_addons::transform(files, std::back_inserter(paths), [](const File& file){
        const auto filePath = file.getFullPathName().toStdString();
        const unsigned int index = [&]() -> unsigned int {
            try
            {
                return static_cast<unsigned int>(std::stoi(file.getFileNameWithoutExtension().substring(0, 2).toStdString()));
            }
            catch(std::exception& e)
            {
                //TODO check return value
                LOG_ERROR(e.what());
                return static_cast<unsigned int>(-1);
            }
        }();

        return std::make_pair(filePath, index);
    });

    std_addons::sort(paths, [](const auto& lhs, const auto& rhs){
        return std::tie(lhs.first, lhs.second) < std::tie(rhs.first, rhs.second);
    });

    return paths;
}

auto readInfoFile(const juce::File& albumDirectory) -> std::tuple<std::vector<std::string>, std::string>
{
    std::vector<std::string> songNames;
    std::string artistName = "";

    Array<File> results;
    if(albumDirectory.findChildFiles(results, File::TypesOfFileToFind::findFiles, false, infoFilePattern) <= 0)
    {
        LOG_WARNING("Could not find any file with pattern \"" << infoFilePattern << "\" in the album " << albumDirectory.getFullPathName());
        return std::tie(songNames, artistName);
    }

    StringArray lines;
    results[0].readLines(lines);

    std::remove_if(lines.begin(), lines.end(), [](const String& current){
       return current.isEmpty();
    });

    if(lines.size() > 0)
    {
        if(lines[0].isNotEmpty())
        {
            artistName = lines[0].toStdString();
            lines.remove(0);
        }

        std_addons::transform(lines, back_inserter(songNames), [](const String& current){
            return current.toStdString();
        });
    }

    return std::tie(songNames, artistName);
}

AlbumInfo loadAlbum(const File& albumDirectory)
{
    Array<File> songFiles;
    if(albumDirectory.findChildFiles(songFiles, File::TypesOfFileToFind::findFiles, false, musicFilePattern) <= 0)
    {
        LOG_WARNING("Could not find any file with pattern \"" << musicFilePattern << "\" in the album " << albumDirectory.getFullPathName());
        return {};
    }

    std_addons::sort(songFiles);

    const unsigned int albumIndex = static_cast<unsigned int>(std::atoi(albumDirectory.getFileName().toStdString().c_str()));

    const auto [songNames, artistName] = readInfoFile(albumDirectory);

    std::vector<jukebox::audio::Song> songs;
    songs.reserve(99);

    if(songNames.size() == static_cast<unsigned int>(songFiles.size()))
    {
        unsigned int songIndex = 1;
        std_addons::transform(songFiles, songNames, std::back_inserter(songs), [&](const File& songFile, const std::string& songName) {
            return createSong(albumIndex, songIndex++, songFile, songName);
        });
    }
    else
    {
        unsigned int songIndex = 1;
        std_addons::transform(songFiles, std::back_inserter(songs), [&](const File& songFile) {
            return createSong(albumIndex, songIndex++, songFile, "");
        });
    }

    std::string imagePath("");
    songFiles.clear();
    if(albumDirectory.findChildFiles(songFiles, File::TypesOfFileToFind::findFiles, false, pictureFilePattern) <= 0)
    {
        LOG_WARNING("Could not find any file with pattern \"" << pictureFilePattern << "\" in the album " << albumDirectory.getFullPathName());
    }
    else
    {
        imagePath = songFiles.begin()->getFullPathName().toStdString();
    }

    return {songs, "", artistName, imagePath, albumIndex};
}

void FileSystem::loadAlbums(std::string_view musicDirectory)
{
    albums.clear();

    File musicDir(std::string{musicDirectory});
    if(!musicDir.isDirectory())
    {
        LOG_ERROR("Non-existent directory: " << musicDirectory);
        return;
    }

    Array<File> results;
    if(musicDir.findChildFiles(results, File::TypesOfFileToFind::findDirectories, false, "???") <= 0)
    {
        LOG_WARNING("Could not find any directory with correct number pattern  \"###\" in the music directory " << musicDir.getFullPathName());
        return;
    }

    std_addons::sort(results);

    albums.reserve(static_cast<size_t>(results.size()));

    std_addons::transform(results, std::back_inserter(albums), [&](const File& albumDirectory) {
        return loadAlbum(albumDirectory);
    });
}

const std::vector<jukebox::audio::AlbumInfo>& FileSystem::getAlbums() const
{
    return albums;
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

jukebox::audio::Song createSong(unsigned int albumNumber, unsigned int songNumber, const juce::File& file, std::string_view name)
{
    return { albumNumber,
             songNumber,
             file.getFullPathName().toStdString(),
             name.empty() ? file.getFileNameWithoutExtension().toStdString() : std::string(name)
    };
}
