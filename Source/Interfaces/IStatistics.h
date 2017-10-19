#ifndef ISTATISTICS_H_INCLUDED
#define ISTATISTICS_H_INCLUDED

#include "Song.h"
#include <iosfwd>

namespace jukebox { namespace statistics {

class IStatistics
{
public:
    virtual ~IStatistics() = default;
    
    virtual void songPlayed(audio::Song song) = 0;
    virtual void albumPlayed(audio::Album album) = 0;

    virtual void coinInserted50() = 0;
    virtual void coinInserted100() = 0;
    virtual void coinInserted200() = 0;
    
    virtual void showStatistics(std::ostream& os) = 0;
};

}}

#endif  // ISTATISTICS_H_INCLUDED
