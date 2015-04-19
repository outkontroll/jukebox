/*
  ==============================================================================

    Statistics.h
    Created: 14 Apr 2015 11:37:11pm
    Author:  adam

  ==============================================================================
*/

#ifndef STATISTICS_H_INCLUDED
#define STATISTICS_H_INCLUDED

#include "IStatistics.h"
#include <map>

namespace jukebox { namespace statistics {

class Statistics : public IStatistics
{
public:
    Statistics();
    ~Statistics();
    
    void songPlayed(audio::Song song) override;
    void albumPlayed(audio::Song album) override;
    
    void showStatistics() override;
    
private:
    typedef std::map<audio::Song, unsigned int> T_PlayedSongs;
    T_PlayedSongs playedSongs;
};

}}

#endif  // STATISTICS_H_INCLUDED
