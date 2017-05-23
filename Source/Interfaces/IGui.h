#ifndef IGUI_H_INCLUDED
#define IGUI_H_INCLUDED

#include "Signals.hpp"
#include "Song.h"

namespace jukebox { namespace gui {
    
class IGui
{
public:
    virtual ~IGui() = default;
    
    virtual void refreshCredits(unsigned int credits) = 0;
    virtual void showStatusMessage(const std::string& message) = 0;
    
    virtual void setMusicFolder(const std::string& folder) = 0;
    
    virtual void enqueue(const audio::Song& song) = 0;
    virtual void removeCurrentSong() = 0;

public:
    jukebox::signals::Signal<> coinInserted50Signal;
    jukebox::signals::Signal<> coinInserted100Signal;
    jukebox::signals::Signal<> coinInserted200Signal;
    
    jukebox::signals::Signal<audio::Song> playSongSignal;
    jukebox::signals::Signal<audio::Album> playAlbumSignal;
    jukebox::signals::Signal<> removePlayedSongSignal;

    jukebox::signals::Signal<> increaseSoundVolumeSignal;
    jukebox::signals::Signal<> decreaseSoundVolumeSignal;
    
    jukebox::signals::Signal<> creditIncreaseSignal;
    jukebox::signals::Signal<> creditDecreaseSignal;
    
    jukebox::signals::Signal<> exitRequestedSignal;
    
    jukebox::signals::Signal<> showStatisticsSignal;

    jukebox::signals::Signal<const audio::Song&> playNextSongSignal;

    jukebox::signals::Signal<> shutDownSignal;
};

}}

#endif  // IGUI_H_INCLUDED
