#ifndef IFILESYSTEM_H
#define IFILESYSTEM_H

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

    virtual void loadAlbums(std::string_view musicDirectory) = 0;
    virtual bool importAlbum(std::string_view musicDirectory, std::string_view albumToImport) = 0;
    virtual const std::vector<jukebox::audio::AlbumInfo>& getAlbums() const = 0;
};

}}

#endif //IFILESYSTEM_H
