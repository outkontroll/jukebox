#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include "IGui.h"
#include <memory>
#include <string>

namespace juce {
    class MainComponent;
    class KeyPress;
}

namespace jukebox {
    class JukeboxTimer;
namespace filesystem {
    class IFileSystem;
}}

class MainWindow;

namespace jukebox { namespace gui {

class Gui : public IGui
{
public:
    Gui(const std::string& applicationName);
    ~Gui() override;

    void refreshCredits(int credits) override;
    void showStatusMessage(ResourceId messageId) override;
    void showInsertedAll(int insertedCoins) override;
    void showInsertedSinceLastSave(int insertedCoins) override;
    void showStatistics(const std::string& statistics) override;
    void refreshAlbums() override;

    void setFileSystem(jukebox::filesystem::IFileSystem* filesys) override;
    void setMusicFolder(const std::string& folder) override;
    void setTimeToPlaySong(int millisecs) override;
    void setTimeToSaveInsertedCoins(int millisecs) override;
    void setTimeToPlayAdvertiseMusic(int millisecs) override;
    void startAdvertiseMusicTimer(int millisecs) override;
    void turnOffAdvertiseMusic() override;
    void setPassword(const Password* password) override;
    void turnOffPassword() override;
    
    void setCurrentlyPlayedSong(const audio::Song& song) override;
    void enqueue(const audio::Song& song) override;
    void removeCurrentSong() override;

    void prepareForExit() override;

protected:
    //this constructor is for testing purposes only
    Gui(std::unique_ptr<juce::MainComponent> mainComp);

private:
    void connectSignals();
    void keyPressed(const juce::KeyPress& key);

    void playNextSong(const audio::Song& song);
    void switchBetweenViews();
    void switchBetweenUserModes();
    void stepSelection();
    void stepSelectionMultipleAlbumsMode();
    void stepSelectionSingleAlbumMode();
    void showHelp();
    void handleAlbumSwitchInAllAlbumMode(bool increase);
    void handleAlbumSwitchInSingleAlbumMode(bool increase);
    void handleAlbumSwitchInMultipleAlbumsMode(bool increase);
    void handleUserInputNumbers(char number);
    void handleDotPressed();
    void musicDirectoryChanged(const std::string& musicDirectory);
    void timeToPlayASongChanged(int millisecs);
    void timeToSaveInsertedCoinsChanged(int millisecs);
    void timeToPlayAdvertiseMusicChanged(int millisecs);
    void passwordChanged(const jukebox::Password& password);
    void passwordTurnedOff();
    void albumImportRequested(const std::string& albumToImport);

    void playSongWithDelay(int albumNumber, int songNumber);
    void playAlbumWithDelay(int albumNumber);

    void loadMultipleAlbums();
    void loadSingleAlbum();

    void stopAdvertiseMusic();

    jukebox::signals::Slot eventsSlot;
    
    std::unique_ptr<juce::MainComponent> mainComponent;
    std::unique_ptr<MainWindow> mainWindow;

    std::unique_ptr<jukebox::JukeboxTimer> secondsToPlayTimer;
    std::unique_ptr<jukebox::JukeboxTimer> playAdvertiseMusicTimer;
    
    std::string userInputSongNumber = "";
    int visibleAlbumsId = 1;
    int selectedAlbumId = 1;
    int albumIndexStep = 8;
    int selectedSongIndex = 0;
    int timeToPlaySong = 0;
    bool isInUserMode = true;
    bool isInMultipleAlbumsMode = true;
    bool isInMusicSetupMode = true;
    bool advertiseMusicPlaying = false;
    jukebox::filesystem::IFileSystem* fileSys = nullptr;
};

}}

#endif  // GUI_H_INCLUDED
