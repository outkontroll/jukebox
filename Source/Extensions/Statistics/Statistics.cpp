#include "Statistics.h"
#include "Formaters.h"
#include "Song.h"
#include <ostream>

using namespace jukebox::statistics;
using namespace jukebox::audio;

void Statistics::songPlayed(const Song& song)
{
    ++playedSongs[song];
}

void Statistics::albumPlayed(const Album& album)
{
    //TODO
    ++playedSongs[Song(album, 0, "")];
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
        os << playedSong.first.toString()
           << ": "
           << playedSong.second
           << std::endl;
    }
}
