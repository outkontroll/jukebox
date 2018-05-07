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

    void refreshCredits(unsigned int credits) override;
    void showStatusMessage(ResourceId messageId) override;
    void showStatistics(const std::string& statistics) override;

    void setFileSystem(jukebox::filesystem::IFileSystem* filesys) override;
    void setMusicFolder(const std::string& folder) override;
    void setTimeToPlaySong(int millisecs) override;
    
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
    void switchBetweenAlbumModes();
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
    //TODO: these two functions could be merged into one entity with templates
    void playSongWithDelay(unsigned int albumNumber, unsigned int songNumber);
    void playAlbumWithDelay(unsigned int albumNumber);

    void loadMultipleAlbums();
    void loadSingleAlbum();

    unsigned int getNextVisibleAlbumsIndex(unsigned int currentVisibleAlbumsIndex, bool increase) const;
    unsigned int getNextSelectedAlbumIndex(unsigned int currentSelectedAlbumIndex, bool increase) const;

    jukebox::signals::Slot eventsSlot;
    
    std::unique_ptr<juce::MainComponent> mainComponent;
    std::unique_ptr<MainWindow> mainWindow;

    std::unique_ptr<jukebox::JukeboxTimer> secondsToPlayTimer;
    
    std::string musicFolder = "";
    std::string userInputSongNumber = "";
    unsigned int visibleAlbumsIndex = 1;
    unsigned int selectedAlbumIndex = 1;
    unsigned int albumIndexStep = 8;
    unsigned int selectedSongIndex = 0;
    unsigned int visibleSongsIndex = 20; //TODO
    int timeToPlaySong = 0;
    bool isInUserMode = true;
    bool isInMultipleAlbumsMode = true;
    jukebox::filesystem::IFileSystem* fileSys = nullptr;
};

}}

#endif  // GUI_H_INCLUDED
