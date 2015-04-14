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

namespace jukebox { namespace statistics {

class Statistics : public IStatistics
{
public:
    Statistics();
    ~Statistics();
    
    void songPlayed(audio::Song song) override;
    void albumPlayed(audio::Song album) override;
};

}}

#endif  // STATISTICS_H_INCLUDED
