#include "Statistics.h"
#include "Song.h"
#include <ostream>
//TODO
#include "SongBuilder.h"
using namespace jukebox::songbuilder;

using namespace jukebox::statistics;
using namespace jukebox::audio;

void Statistics::songPlayed(const Song& song)
{
    ++playedSongs[song];
}

void Statistics::albumPlayed(const Album& album)
{
    //TODO
    auto song = SongBuilder::buildSong(album.getAlbumNumber(), 0, "albumTesting");
    ++playedSongs[song];
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

    for(const auto& playedSong : playedSongs)
    {
        os << playedSong.first.visibleName
           << ": "
           << playedSong.second
           << std::endl;
    }
}
