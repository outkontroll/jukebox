#ifndef SONG_H_INCLUDED
#define SONG_H_INCLUDED

#include <tuple>
#include <string>
#include <vector>

namespace jukebox { namespace audio {

struct Album
{
    inline bool operator<(const Album& other) const
    {
        return albumNumber < other.albumNumber;
    }

    inline bool operator==(const Album& other) const
    {
        return albumNumber == other.albumNumber;
    }

    const unsigned int albumNumber;
    const std::string visibleName;
};

struct Song
{
    inline bool operator<(const Song& other) const
    {
        return std::tie(albumNumber, songNumber, fileName) < std::tie(other.albumNumber, other.songNumber, other.fileName);
    }

    inline bool operator==(const Song& other) const
    {
        return std::tie(albumNumber, songNumber, fileName) == std::tie(other.albumNumber, other.songNumber, other.fileName);
    }

    const unsigned int albumNumber;
    const unsigned int songNumber;
    const std::string fileName;
    const std::string visibleName;
};

struct AlbumInfo
{
    inline bool operator==(const AlbumInfo& other) const
    {
        return id == other.id && title == other.title && artist == other.artist && imagePath == other.imagePath && textFilePath == other.textFilePath && songs == other.songs;
    }

    const std::vector<Song> songs;
    const std::string title;
    const std::string artist;
    const std::string imagePath;
    const std::string textFilePath;
    const unsigned int id;
};

}}

#endif  // SONG_H_INCLUDED
