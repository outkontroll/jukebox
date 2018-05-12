#ifndef FILESYSTEM_H_INCLUDED
#define FILESYSTEM_H_INCLUDED

#include <string>
#include <tuple>
#include "IFileSystem.h"

namespace juce {
    class File;
}

namespace jukebox { namespace filesystem {

class FileSystem : public IFileSystem
{
public:
    ~FileSystem() override = default;

    void loadAlbums(std::string_view musicDirectory) override;
    bool importAlbum(std::string_view musicDirectory, std::string_view albumToImport) override;
    const std::vector<jukebox::audio::AlbumInfo>& getAlbums() const override;
private:
    jukebox::audio::AlbumInfo loadAlbum(const juce::File& albumDirectory);
    std::tuple<std::vector<std::string>, std::string, std::string> readInfoFile(const juce::File& albumDirectory);
    bool checkImportPreconditions(const juce::File& musicDir, const juce::File& albumDir) const;
    bool renameImportedMusicFiles(const juce::File& albumDir, unsigned int albumId);

    std::vector<jukebox::audio::AlbumInfo> albums;
};

}}


#endif  // FILESYSTEM_H_INCLUDED
