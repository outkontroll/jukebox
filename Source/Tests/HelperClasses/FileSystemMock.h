#ifndef FILESYSTEMMOCK_H
#define FILESYSTEMMOCK_H

#include "IFileSystem.h"
#include "gmock/gmock.h"

struct FileSystemMock : public jukebox::filesystem::IFileSystem
{
    MOCK_CONST_METHOD3(getPicturePath, std::string(const std::string&, unsigned int, const std::string&));
    MOCK_CONST_METHOD2(getInfoFilePath, std::string(const std::string&, unsigned int));
    MOCK_CONST_METHOD4(getSongFilePath, std::string(const std::string&, unsigned int, unsigned int, const std::string&));
    MOCK_CONST_METHOD3(getAllSongFilesWithFullPaths, std::vector<std::pair<std::string, unsigned int>>(const std::string&, unsigned int, const std::string&));
    MOCK_METHOD1(loadAlbums, void(std::string_view));
    MOCK_CONST_METHOD0(getAlbums, const std::vector<jukebox::audio::AlbumInfo>&());
};

#endif //FILESYSTEMMOCK_H
