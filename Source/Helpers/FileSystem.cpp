#include "FileSystem.h"
#include "Formaters.h"
#include "Logger.h"
#include "JuceHeader.h"

using namespace jukebox::filesystem;
using namespace juce;

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

std::string FileSystem::getInfoFilePath(const std::string& musicDirectory, int albumIndex)
{
    if(musicDirectory == "")
    {
        LOG_WARNING("called with empty path!");
        return {};
    }

    //TODO get actal file, not just by guessing
    return musicDirectory + "/" + FillWithLeadingZeros(albumIndex, 3) + "/eloado.txt";
}

std::string FileSystem::getSongFilePath(const std::string& musicDirectory, const String& albumDir, const std::string& songNum, const std::string& extensionPattern)
{
    File musicDir(musicDirectory);
    if(!musicDir.isDirectory())
    {
        LOG_ERROR("Non-existant directory: " << musicDirectory);
        return "";
    }

    File albumDirextory = musicDir.getChildFile(albumDir);
    if(!albumDirextory.isDirectory())
    {
        LOG_ERROR("Non-existant directory: " << albumDirextory.getFileName());
        return "";
    }

    //TODO iterate through all the patterns and include the song number in front of the asterisk
    String wildCardPattern(songNum + extensionPattern);
    Array<File> results;
    if(albumDirextory.findChildFiles(results, File::TypesOfFileToFind::findFiles, false, wildCardPattern) <= 0)
    {
        LOG_ERROR("Could not find any file beginning with " << songNum << " and with an extension one of " << extensionPattern);
        return "";
    }

    return results[0].getFullPathName().toStdString();
}
