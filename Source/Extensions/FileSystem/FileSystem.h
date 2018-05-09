#ifndef FILESYSTEM_H_INCLUDED
#define FILESYSTEM_H_INCLUDED

#include "IFileSystem.h"

namespace jukebox { namespace filesystem {

class FileSystem : public IFileSystem
{
public:
    ~FileSystem() override = default;

    std::string getSongFilePath(const std::string& musicDirectory, unsigned int albumIndex, unsigned int songIndex, const std::string& extensionPattern) const override;
    std::vector<std::pair<std::string, unsigned int>> getAllSongFilesWithFullPaths(const std::string& musicDicertory, unsigned int albumIndex, const std::string& extensionPattern) const override;

    void loadAlbums(std::string_view musicDirectory) override;
    const std::vector<jukebox::audio::AlbumInfo>& getAlbums() const override;
private:
    std::vector<jukebox::audio::AlbumInfo> albums;
};

}}


#endif  // FILESYSTEM_H_INCLUDED
