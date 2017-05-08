#include "Statistics.h"
#include "Formaters.h"
#include <ostream>

using namespace jukebox::statistics;
using namespace jukebox::audio;

void Statistics::songPlayed(Song song)
{
    ++playedSongs[song];
}

void Statistics::albumPlayed(Album album)
{
    //TODO
    ++playedSongs[Song(album, 0)];
}

void Statistics::showStatistics(std::ostream& os)
{
    for(auto playedSong : playedSongs)
    {
        os << FillWithLeadingZeros(playedSong.first.getAlbumNumber(), 3)
           << FillWithLeadingZeros(playedSong.first.getSongNumber(), 2)
           << ": "
           << playedSong.second
           << std::endl;
    }
}
