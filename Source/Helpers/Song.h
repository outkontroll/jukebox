#ifndef SONG_H_INCLUDED
#define SONG_H_INCLUDED

#include <tuple>
#include <string>

namespace jukebox { namespace audio {

class Album
{
public:
    explicit Album(unsigned int albumNumber_)
    : albumNumber(albumNumber_)
    {
    }

    inline unsigned int getAlbumNumber() const
    {
        return albumNumber;
    }
private:
    const unsigned int albumNumber;
};

class Song
{
public:
    Song(unsigned int albumNumber_, unsigned int songNumber_, const std::string& fileName_, const std::string& visibleName_)
    :   albumNumber(albumNumber_),
        songNumber(songNumber_),
        fileName(fileName_),
        visibleName(visibleName_)
    {
    }

    inline unsigned int getAlbumNumber() const
    {
        return albumNumber;
    }

    inline unsigned int getSongNumber() const
    {
        return songNumber;
    }

    inline const std::string& getFileName() const
    {
        return fileName;
    }

    inline bool operator<(const Song& other) const
    {
        return std::tie(albumNumber, songNumber, fileName) < std::tie(other.albumNumber, other.songNumber, fileName);
    }

    inline bool operator==(const Song& other) const
    {
        return std::tie(albumNumber, songNumber, fileName) == std::tie(other.albumNumber, other.songNumber, fileName);
    }

    inline const std::string& toString() const
    {
        return visibleName;
    }

private:
    const unsigned int albumNumber = 0;
    const unsigned int songNumber = 0;
    const std::string fileName = "";
    const std::string visibleName = "";
};

}}

#endif  // SONG_H_INCLUDED
