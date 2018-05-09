#ifndef IFILESYSTEM_H
#define IFILESYSTEM_H

#include <string>
#include <vector>
#include <string_view>


namespace jukebox {
namespace audio {
    struct AlbumInfo;
}

namespace filesystem {

class IFileSystem
{
public:
    virtual ~IFileSystem() = default;

    virtual std::string getSongFilePath(const std::string& musicDirectory, unsigned int albumIndex, unsigned int songIndex, const std::string& extensionPattern) const = 0;
    virtual std::vector<std::pair<std::string, unsigned int>> getAllSongFilesWithFullPaths(const std::string& musicDicertory, unsigned int albumIndex, const std::string& extensionPattern) const = 0;

    virtual void loadAlbums(std::string_view musicDirectory) = 0;
    virtual const std::vector<jukebox::audio::AlbumInfo>& getAlbums() const = 0;
};

}}

#endif //IFILESYSTEM_H
