#ifndef STATISTICSMOCK_H
#define STATISTICSMOCK_H

#include "IStatistics.h"
#include "gmock/gmock.h"

struct StatisticsMock : public jukebox::statistics::IStatistics
{
    // IStatistics interface
public:
    MOCK_METHOD1(songPlayed, void(jukebox::audio::Song));
    MOCK_METHOD1(albumPlayed, void(jukebox::audio::Album));
    MOCK_METHOD1(showStatistics, void(std::ostream&));
    MOCK_METHOD0(coinInserted50, void());
    MOCK_METHOD0(coinInserted100, void());
    MOCK_METHOD0(coinInserted200, void());
};

#endif // STATISTICSMOCK_H
