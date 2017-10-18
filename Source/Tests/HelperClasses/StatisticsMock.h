#ifndef STATISTICSMOCK_H
#define STATISTICSMOCK_H

#include "IStatistics.h"

struct StatisticsMock : public jukebox::statistics::IStatistics
{

    // IStatistics interface
public:
    void songPlayed(jukebox::audio::Song) override
    {
    }
    void albumPlayed(jukebox::audio::Album) override
    {
    }
    void showStatistics(std::ostream&) override
    {
    }
};

#endif // STATISTICSMOCK_H
