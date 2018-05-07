#include "Statistics.h"
#include <ostream>
#include <fstream>
#include "JukeboxTimer.h"
#include "Song.h"
#include "Times.h"

using namespace jukebox::statistics;
using namespace jukebox::audio;

namespace {
    const auto fileName = "insertedCoins.txt";
}

Statistics::~Statistics() = default;

Statistics::Statistics() = default;

void Statistics::songPlayed(const Song& song)
{
    ++playedSongs[song];
}

void Statistics::albumPlayed(const Album& album)
{
    ++playedAlbums[album];
}

void Statistics::coinInserted50()
{
    insertedCoinsAllTime += 50;
    insertedCoinsToday += 50;
}

void Statistics::coinInserted100()
{
    insertedCoinsAllTime += 100;
    insertedCoinsToday += 100;
}

void Statistics::coinInserted200()
{
    insertedCoinsAllTime += 200;
    insertedCoinsToday += 200;
}

void Statistics::setSaveTimeout(int millisecs)
{
    saveTimer = std::make_unique<JukeboxTimer>([this](){
        std::ofstream f(fileName, std::ios::app);
        if(f)
        {
            f << jukebox::CurrentDateTime() << ": " << insertedCoinsToday << std::endl;
        }

        insertedCoinsToday = 0;
    });

    saveTimer->startTimer(millisecs);
}

void Statistics::showStatistics(std::ostream& os)
{
    os << "Inserted: " << insertedCoinsAllTime << std::endl;
    os << "Inserted since last save: " << insertedCoinsToday << std::endl;

    for(const auto& album : playedAlbums)
    {
        os << album.first.visibleName
           << ": "
           << album.second
           << std::endl;
    }

    for(const auto& playedSong : playedSongs)
    {
        os << playedSong.first.visibleName
           << ": "
           << playedSong.second
           << std::endl;
    }
}
