#ifndef STATISTICS_H_INCLUDED
#define STATISTICS_H_INCLUDED

#include <map>
#include <memory>
#include "IStatistics.h"
#include "Song.h"

namespace jukebox {
    class JukeboxTimer;
}

namespace jukebox { namespace statistics {

class Statistics : public IStatistics
{
public:
    Statistics();
    ~Statistics() override;

    void songPlayed(const audio::Song&) override;
    void albumPlayed(const audio::Album&) override;

    void coinInserted50() override;
    void coinInserted100() override;
    void coinInserted200() override;

    void setSaveTimeout(int millisecs) override;
    
    int getInsertedAll() const override;
    int getInsertedSinceLastSave() const override;
    void showStatistics(std::ostream& os) const override;
    
private:
    std::map<audio::Song, unsigned int> playedSongs;
    std::map<audio::Album, unsigned int> playedAlbums;
    std::unique_ptr<jukebox::JukeboxTimer> saveTimer;
    int insertedCoinsAllTime = 0;
    int insertedCoinsToday = 0;
};

}}

#endif  // STATISTICS_H_INCLUDED
