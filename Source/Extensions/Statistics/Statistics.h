#ifndef STATISTICS_H_INCLUDED
#define STATISTICS_H_INCLUDED

#include "IStatistics.h"
#include <map>

namespace jukebox { namespace statistics {

class Statistics : public IStatistics
{
public:
    void songPlayed(audio::Song song) override;
    void albumPlayed(audio::Song album) override;
    
    void showStatistics(std::ostream& os) override;
    
private:
    typedef std::map<audio::Song, unsigned int> T_PlayedSongs;
    T_PlayedSongs playedSongs;
};

}}

#endif  // STATISTICS_H_INCLUDED
