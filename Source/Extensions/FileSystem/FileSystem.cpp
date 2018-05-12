#include "FileSystem.h"
#include <algorithm>
#include <utility>
#include <cassert>
#include "JuceHeader.h"
#include "SongBuilder.h"
#include "StdAddons.hpp"
#include "Logger.h"
#include "Song.h"

using namespace jukebox::filesystem;
using namespace jukebox::audio;
using namespace jukebox::songbuilder;
using namespace juce;

namespace {
    const auto musicFilePattern = "??*.mp3"; // exclude 1.mp3 and likes
    const auto infoFilePattern = "*.txt";
    const auto pictureFilePattern = "*.jpg";
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

AlbumInfo FileSystem::loadAlbum(const File& albumDirectory)
{
    Array<File> songFiles;
    if(albumDirectory.findChildFiles(songFiles, File::TypesOfFileToFind::findFiles, false, musicFilePattern) <= 0)
    {
        LOG_WARNING("Could not find any file with pattern \"" << musicFilePattern << "\" in the album " << albumDirectory.getFullPathName());
        return {};
    }

    std_addons::sort(songFiles);

    const unsigned int albumIndex = static_cast<unsigned int>(std::atoi(albumDirectory.getFileName().toStdString().c_str()));

    const auto [songNames, artistName, txtFilePath] = readInfoFile(albumDirectory);

    std::vector<jukebox::audio::Song> songs;
    songs.reserve(99);

    if(songNames.size() == static_cast<unsigned int>(songFiles.size()))
    {
        unsigned int songIndex = 1;
        std_addons::transform(songFiles, songNames, std::back_inserter(songs), [&](const File& songFile, const std::string& songName) {
            return SongBuilder::buildSong(albumIndex, songIndex++, songFile, songName);
        });
    }
    else
    {
        unsigned int songIndex = 1;
        std_addons::transform(songFiles, std::back_inserter(songs), [&](const File& songFile) {
            return SongBuilder::buildSong(albumIndex, songIndex++, songFile, "");
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

    return {songs, "", artistName, imagePath, txtFilePath, albumIndex};
}

auto FileSystem::readInfoFile(const juce::File& albumDirectory) -> std::tuple<std::vector<std::string>, std::string, std::string>
{
    std::vector<std::string> songNames;
    std::string artistName = "";

    Array<File> results;
    if(albumDirectory.findChildFiles(results, File::TypesOfFileToFind::findFiles, false, infoFilePattern) <= 0)
    {
        LOG_WARNING("Could not find any file with pattern \"" << infoFilePattern << "\" in the album " << albumDirectory.getFullPathName());
        return std::tie(songNames, artistName, "");
    }

    const std::string txtFileName = results[0].getFullPathName().toStdString();
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

    return std::tie(songNames, artistName, txtFileName);
}
