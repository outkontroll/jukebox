#ifndef FILESYSTEMMOCK_H
#define FILESYSTEMMOCK_H

#include "IFileSystem.h"
#include "gmock/gmock.h"

struct FileSystemMock : public jukebox::filesystem::IFileSystem
{
    MOCK_CONST_METHOD3(getPicturePath, std::string(const std::string&, int, const std::string&));
    MOCK_CONST_METHOD2(getInfoFilePath, std::string(const std::string&, int));
    MOCK_CONST_METHOD4(getSongFilePath, std::string(const std::string&, int, int, const std::string&));
    MOCK_CONST_METHOD3(getAllSongFilesWithFullPaths, std::vector<std::pair<std::string, int>>(const std::string&, int, const std::string&));
    MOCK_CONST_METHOD3(getAllSongFilesNamesOnly, std::vector<std::string>(const std::string&, int, const std::string&));
};

#endif //FILESYSTEMMOCK_H