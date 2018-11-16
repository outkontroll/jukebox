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

    const int albumNumber;
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

    const int albumNumber;
    const int songNumber;
    const std::string fileName;
    const std::string visibleName;
};

struct AlbumInfo
{
    inline bool operator==(const AlbumInfo& other) const
    {
        return std::tie(id, title, artist, imagePath, textFilePath, songs) == std::tie(other.id, other.title, other.artist, other.imagePath, other.textFilePath, other.songs);
    }

    const std::vector<Song> songs;
    const std::string title;
    const std::string artist;
    const std::string imagePath;
    const std::string textFilePath;
    const int id;
};

}}

#endif  // SONG_H_INCLUDED
