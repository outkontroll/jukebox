#include "FileSystem.h"
#include "Formaters.h"
#include "Logger.h"
#include "JuceHeader.h"

using namespace jukebox::filesystem;
using namespace juce;

std::string getFilePathInAlbum(const std::string& musicDirectory, const String& albumDir, const std::string& wildCardPattern);

std::string FileSystem::getPicturePath(const std::string& musicDirectory, int albumIndex, const std::string& pictureExtensions)
{
    std::string wildCardPattern("*" + pictureExtensions);
    return getFilePathInAlbum(musicDirectory, FillWithLeadingZeros(albumIndex, 3), wildCardPattern);
}

std::string FileSystem::getInfoFilePath(const std::string& musicDirectory, int albumIndex)
{
    return getFilePathInAlbum(musicDirectory, FillWithLeadingZeros(albumIndex, 3), "*.txt");
}

std::string FileSystem::getSongFilePath(const std::string& musicDirectory, int albumIndex, int songIndex, const std::string& extensionPattern)
{
    //TODO iterate through all the patterns and include the song number in front of the asterisk
    std::string wildCardPattern(FillWithLeadingZeros(songIndex, 2) + extensionPattern);
    return getFilePathInAlbum(musicDirectory, FillWithLeadingZeros(albumIndex, 3), wildCardPattern);
}

std::string getFilePathInAlbum(const std::string& musicDirectory, const String& albumDir, const std::string& wildCardPattern)
{
    File musicDir(musicDirectory);
    if(!musicDir.isDirectory())
    {
        LOG_ERROR("Non-existent directory: " << musicDirectory);
        return "";
    }

    File albumDirextory = musicDir.getChildFile(albumDir);
    if(!albumDirextory.isDirectory())
    {
        LOG_ERROR("Non-existent directory: " << albumDirextory.getFileName());
        return "";
    }

    Array<File> results;
    if(albumDirextory.findChildFiles(results, File::TypesOfFileToFind::findFiles, false, wildCardPattern) <= 0)
    {
        LOG_WARNING("Could not find any file with pattern \"" << wildCardPattern << "\" in the album " << albumDirextory.getFullPathName());
        return "";
    }

    return results[0].getFullPathName().toStdString();
}
