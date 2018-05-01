#ifndef STATISTICS_H_INCLUDED
#define STATISTICS_H_INCLUDED

#include "IStatistics.h"
#include "Song.h"
#include <map>

namespace jukebox { namespace statistics {

class Statistics : public IStatistics
{
public:
    void songPlayed(const audio::Song&) override;
    void albumPlayed(const audio::Album&) override;

    void coinInserted50() override;
    void coinInserted100() override;
    void coinInserted200() override;
    
    void showStatistics(std::ostream& os) override;
    
private:
    std::map<audio::Song, unsigned int> playedSongs;
    std::map<audio::Album, unsigned int> playedAlbums;
    int insertedCoins = 0;
};

}}

#endif  // STATISTICS_H_INCLUDED
