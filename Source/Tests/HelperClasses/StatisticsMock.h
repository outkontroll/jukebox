#ifndef STATISTICSMOCK_H
#define STATISTICSMOCK_H

#include "IStatistics.h"
#include "Song.h"
#include "gmock/gmock.h"

struct StatisticsMock : public jukebox::statistics::IStatistics
{
    // IStatistics interface
public:
    MOCK_METHOD1(songPlayed, void(const jukebox::audio::Song&));
    MOCK_METHOD1(albumPlayed, void(const jukebox::audio::Album&));
    MOCK_METHOD1(setSaveTimeout, void(int));
    MOCK_CONST_METHOD0(getInsertedAll, int());
    MOCK_CONST_METHOD0(getInsertedSinceLastSave, int());
    MOCK_CONST_METHOD1(showStatistics, void(std::ostream&));
    MOCK_METHOD0(coinInserted50, void());
    MOCK_METHOD0(coinInserted100, void());
    MOCK_METHOD0(coinInserted200, void());
};

#endif // STATISTICSMOCK_H
