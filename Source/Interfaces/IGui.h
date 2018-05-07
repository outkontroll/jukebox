#ifndef IGUI_H_INCLUDED
#define IGUI_H_INCLUDED

#include "Signals.hpp"

namespace jukebox {
    enum class ResourceId;
namespace audio {
    struct Song;
    struct Album;
}
namespace filesystem {
    class IFileSystem;
}
}

namespace jukebox { namespace gui {
    
class IGui
{
public:
    virtual ~IGui() = default;
    
    virtual void refreshCredits(unsigned int credits) = 0;
    virtual void showStatusMessage(ResourceId messageId) = 0;
    virtual void showStatistics(const std::string& statistics) = 0;
    
    virtual void setFileSystem(jukebox::filesystem::IFileSystem* fileSys) = 0;
    virtual void setMusicFolder(const std::string& folder) = 0;
    virtual void setTimeToPlaySong(int millisecs) = 0;
    virtual void setTimeToSaveInsertedCoins(int millisecs) = 0;
    
    virtual void setCurrentlyPlayedSong(const audio::Song&) = 0;
    virtual void enqueue(const audio::Song& song) = 0;
    virtual void removeCurrentSong() = 0;

    virtual void prepareForExit() = 0;

public:
    jukebox::signals::Signal<> coinInserted50Signal;
    jukebox::signals::Signal<> coinInserted100Signal;
    jukebox::signals::Signal<> coinInserted200Signal;    
    jukebox::signals::Signal<> creditIncreaseSignal;
    jukebox::signals::Signal<> creditDecreaseSignal;

    jukebox::signals::Signal<const audio::Song&> playSongSignal;
    jukebox::signals::Signal<const audio::Album&, const std::vector<audio::Song>&> playAlbumSignal;
    jukebox::signals::Signal<> removePlayedSongSignal;
    jukebox::signals::Signal<const audio::Song&> playNextSongSignal;

    jukebox::signals::Signal<> increaseSoundVolumeSignal;
    jukebox::signals::Signal<> decreaseSoundVolumeSignal;
    jukebox::signals::Signal<> switchMuteStatusSignal;

    jukebox::signals::Signal<const std::string&> musicDirectoryChangedSignal;
    jukebox::signals::Signal<int> timeToPlayASongChangedSignal;
    jukebox::signals::Signal<int> timeToSaveInsertedCoinsChangedSignal;

    jukebox::signals::Signal<> requestStatisticsSignal;

    jukebox::signals::Signal<> exitRequestedSignal;
    jukebox::signals::Signal<> shutDownSignal;
};

}}

#endif  // IGUI_H_INCLUDED
