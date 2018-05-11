#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include <memory>
#include "Signals.hpp"

namespace jukebox {
    class Password;
namespace gui {
    class IGui;
}
namespace creditmanager {
    class ICreditManager;
}
namespace audio {
    class IMusicPlayer;
    struct Song;
    struct Album;
}
namespace statistics {
    class IStatistics;
}
namespace settings {
    class ISettings;
}
namespace filesystem {
    class IFileSystem;
}
namespace core {

class Core
{
public:
    Core(std::unique_ptr<gui::IGui> iGui,
         std::unique_ptr<creditmanager::ICreditManager> iCreditManager,
         std::unique_ptr<audio::IMusicPlayer> iMusicPlayer,
         std::unique_ptr<statistics::IStatistics> iStatistics,
         std::unique_ptr<settings::ISettings> iSettings,
         std::unique_ptr<filesystem::IFileSystem> iFileSystem);

    //TODO: this should be private
    jukebox::signals::Signal<> exitRequestedSignal;

private:
    void coinInserted50();
    void coinInserted100();
    void coinInserted200();
    void creditIncrease();
    void creditDecrease();
    
    void playSong(const audio::Song& song);
    void playAlbum(const audio::Album& album, const std::vector<audio::Song>& songs);
    void removePlayedSong();
    void finishedPlaying();
    void playNextSong(const audio::Song& song);
    void playOrEnqueue(const audio::Song& song);
    
    void musicDirectoryChanged(const std::string& newMusicDirectory);
    void timeToPlayASongChanged(int millisecs);
    void timeToSaveInsertedCoinsChanged(int millisecs);
    void passwordChanged(const jukebox::Password& password);
    void passwordTurnedOff();

    void showStatisticsRequested();
    void exitRequested();

    jukebox::signals::Slot eventsSlot;
    std::unique_ptr<gui::IGui> gui;
    std::unique_ptr<creditmanager::ICreditManager> creditManager;
    std::unique_ptr<audio::IMusicPlayer> musicPlayer;
    std::unique_ptr<statistics::IStatistics> statistics;
    std::unique_ptr<settings::ISettings> settings;
    std::unique_ptr<filesystem::IFileSystem> fileSys;
};

}}

#endif  // CORE_H_INCLUDED
