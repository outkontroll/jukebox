#ifndef ISTATISTICS_H_INCLUDED
#define ISTATISTICS_H_INCLUDED

#include <iosfwd>

namespace jukebox { namespace audio {
    struct Song;
    struct Album;
}}

namespace jukebox { namespace statistics {

class IStatistics
{
public:
    virtual ~IStatistics() = default;
    
    virtual void songPlayed(const audio::Song& song) = 0;
    virtual void albumPlayed(const audio::Album& album) = 0;

    virtual void coinInserted50() = 0;
    virtual void coinInserted100() = 0;
    virtual void coinInserted200() = 0;

    virtual void setSaveTimeout(int millisecs) = 0;
    
    virtual int getInsertedAll() const = 0;
    virtual int getInsertedSinceLastSave() const = 0;
    virtual void showStatistics(std::ostream& os) const = 0;
};

}}

#endif  // ISTATISTICS_H_INCLUDED
