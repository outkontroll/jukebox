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

bool FileSystem::importAlbum(std::string_view musicDirectory, std::string_view albumToImport)
{
    File musicDir(std::string{musicDirectory});
    File albumDir(std::string{albumToImport});

    if(!checkImportPreconditions(musicDir, albumDir))
        return false;

    const auto albumId = albums.back().id + 1;

    const File newAlbum = musicDir.getChildFile(String{SongBuilder::createVisibleName(albumId)});
    if(newAlbum.exists())
    {
        LOG_ERROR("Can not create new album!");
        return false;
    }

    if(!albumDir.copyDirectoryTo(newAlbum))
    {
        LOG_ERROR("Can not copy the files into the album!");
        return false;
    }

    renameImportedMusicFiles(albumDir, albumId);

    albums.push_back(loadAlbum(newAlbum));

    return true;
}

const std::vector<jukebox::audio::AlbumInfo>& FileSystem::getAlbums() const
{
    return albums;
}

AlbumInfo FileSystem::loadAlbum(const File& albumDirectory)
{
    const unsigned int albumId = static_cast<unsigned int>(std::atoi(albumDirectory.getFileName().toStdString().c_str()));

    Array<File> songFiles;
    if(albumDirectory.findChildFiles(songFiles, File::TypesOfFileToFind::findFiles, false, musicFilePattern) <= 0)
    {
        LOG_WARNING("Could not find any file with pattern \"" << musicFilePattern << "\" in the album " << albumDirectory.getFullPathName());
        return {{}, "", "", "", "", albumId};
    }

    std_addons::sort(songFiles);

    if(songFiles.size() > 99)
    {
        songFiles.removeLast(songFiles.size() - 99);
    }

    const auto [songNames, artistName, txtFilePath] = readInfoFile(albumDirectory);

    std::vector<jukebox::audio::Song> songs;
    songs.reserve(99);

    if(songNames.size() == static_cast<unsigned int>(songFiles.size()))
    {
        unsigned int songIndex = 1;
        std_addons::transform(songFiles, songNames, std::back_inserter(songs), [&](const File& songFile, const std::string& songName) {
            return SongBuilder::buildSong(albumId, songIndex++, songFile, songName);
        });
    }
    else
    {
        unsigned int songIndex = 1;
        std_addons::transform(songFiles, std::back_inserter(songs), [&](const File& songFile) {
            return SongBuilder::buildSong(albumId, songIndex++, songFile, "");
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

    return {songs, "", artistName, imagePath, txtFilePath, albumId};
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

bool FileSystem::checkImportPreconditions(const File& musicDir, const File& albumDir) const
{
    if(musicDir == albumDir)
    {
        LOG_ERROR("Can not import the music directory to itself!");
        return false;
    }

    if(!musicDir.isDirectory())
    {
        LOG_ERROR("Non-existent directory: " << musicDir.getFullPathName());
        return false;
    }

    if(!albumDir.isDirectory())
    {
        LOG_ERROR("The given album is not a directory: " << albumDir.getFullPathName());
        return false;
    }

    if(!musicDir.hasWriteAccess())
    {
        LOG_ERROR("Does not have write access to music directory " << musicDir.getFullPathName());
        return false;
    }

    if(musicDir.getNumberOfChildFiles(File::findDirectories, "???") >= 999)
    {
        LOG_ERROR("Music directory is full, try deleting something first!");
        return false;
    }

    return true;
}

bool FileSystem::renameImportedMusicFiles(const File& albumDir, unsigned int albumId)
{
    Array<File> results;
    if(albumDir.findChildFiles(results, File::findFiles, false, musicFilePattern) <= 0)
    {
        LOG_ERROR("There was no music file in the imported directory " << albumDir.getFullPathName());
        return false;
    }

    std_addons::sort(results, [](const File& lhs, const File& rhs){
        return lhs.getFileName() < rhs.getFileName();
    });


    unsigned int songId = 1;
    for(auto& songFile : results)
    {
        const String id = SongBuilder::createVisibleName(albumId, songId++).substr(3);
        if(!songFile.getFileNameWithoutExtension().startsWith(id))
        {
            const File renamedFile = songFile.getParentDirectory().getChildFile(id + " " + songFile.getFileName());
            if(!songFile.moveFileTo(renamedFile))
            {
                LOG_WARNING("Could not rename file " << renamedFile.getFileName());
            }
        }
    }

    return true;
}
