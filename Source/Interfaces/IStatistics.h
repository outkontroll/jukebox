/*
  ==============================================================================

    IStatistics.h
    Created: 14 Apr 2015 11:32:09pm
    Author:  adam

  ==============================================================================
*/

#ifndef ISTATISTICS_H_INCLUDED
#define ISTATISTICS_H_INCLUDED

#include "Song.h"

namespace jukebox { namespace statistics {

class IStatistics
{
public:
    virtual ~IStatistics() = default;
    
    virtual void songPlayed(audio::Song song) = 0;
    virtual void albumPlayed(audio::Song album) = 0;
    
    virtual void showStatistics() = 0;
};

}}

#endif  // ISTATISTICS_H_INCLUDED
