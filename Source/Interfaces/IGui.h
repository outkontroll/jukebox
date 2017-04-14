#ifndef IGUI_H_INCLUDED
#define IGUI_H_INCLUDED

#include "Signals.hpp"
//TODO: check if this is not needed...
#include "Song.h"

namespace jukebox { namespace gui {
    
class IGui
{
public:
    virtual ~IGui() = default;
    
    virtual void initialize(const std::string& name) = 0;
    virtual void uninitialize() = 0;
    
    virtual void refreshCredits(unsigned int credits) = 0;
    virtual void showStatusMessage(const std::string& message) = 0;
    
    virtual void setMusicFolder(const std::string& folder) = 0;
    
    virtual void enqueue(const std::string& song) = 0;
    virtual void removeNextSong() = 0;

public:
    jukebox::signals::Signal<> coinInserted50Signal;
    jukebox::signals::Signal<> coinInserted100Signal;
    jukebox::signals::Signal<> coinInserted200Signal;
    
    jukebox::signals::Signal<audio::Song> playSongSignal;
    jukebox::signals::Signal<audio::Album> playAlbumSignal;
    jukebox::signals::Signal<> removePlayedSongSignal;
    
    jukebox::signals::Signal<> creditIncreaseSignal;
    jukebox::signals::Signal<> creditDecreaseSignal;
    
    jukebox::signals::Signal<> exitRequestedSignal;
    
    jukebox::signals::Signal<> showStatisticsSignal;
};

}}

#endif  // IGUI_H_INCLUDED
