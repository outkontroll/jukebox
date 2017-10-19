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

void Statistics::coinInserted50()
{
    insertedCoins += 50;
}

void Statistics::coinInserted100()
{
    insertedCoins += 100;
}

void Statistics::coinInserted200()
{
    insertedCoins += 200;
}

void Statistics::showStatistics(std::ostream& os)
{
    os << "Inserted: " << insertedCoins << std::endl;

    for(auto playedSong : playedSongs)
    {
        os << FillWithLeadingZeros(playedSong.first.getAlbumNumber(), 3)
           << FillWithLeadingZeros(playedSong.first.getSongNumber(), 2)
           << ": "
           << playedSong.second
           << std::endl;
    }
}
