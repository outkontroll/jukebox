#ifndef FILESYSTEMMOCK_H
#define FILESYSTEMMOCK_H

#include "IFileSystem.h"
#include "gmock/gmock.h"

struct FileSystemMock : public jukebox::filesystem::IFileSystem
{
    MOCK_METHOD1(loadAlbums, void(std::string_view));
    MOCK_METHOD2(importAlbum, bool(std::string_view, std::string_view));
    MOCK_CONST_METHOD0(getAlbums, const std::vector<jukebox::audio::AlbumInfo>&());
};

#endif //FILESYSTEMMOCK_H
