#ifndef STATISTICS_H_INCLUDED
#define STATISTICS_H_INCLUDED

#include "IStatistics.h"
#include <map>

namespace jukebox { namespace statistics {

class Statistics : public IStatistics
{
public:
    void songPlayed(audio::Song) override;
    void albumPlayed(audio::Album) override;
    
    void showStatistics(std::ostream& os) override;
    
private:
    using T_PlayedSongs = std::map<audio::Song, unsigned int>;
    T_PlayedSongs playedSongs;
};

}}

#endif  // STATISTICS_H_INCLUDED
