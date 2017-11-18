#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include "JuceHeader.h"
#include "IGui.h"
#include <memory>
#include <string>

namespace juce {
    class MainComponent;
}

class MainWindow;

namespace jukebox { namespace gui {

class JukeboxTimer;

class Gui : public IGui
{
public:
    Gui(const std::string& applicationName);
    ~Gui();

    void refreshCredits(unsigned int credits) override;
    void showStatusMessage(ResourceId messageId) override;
    
    void setMusicFolder(const std::string& folder) override;
    
    void setCurrentlyPlayedSong(const audio::Song& song) override;
    void enqueue(const audio::Song& song) override;
    void removeCurrentSong() override;

    void prepareForExit() override;

protected:
    //this constructor is for testing purposes only
    Gui(std::unique_ptr<juce::MainComponent> mainComp);

private:
    void keyPressed(const juce::KeyPress& key);

    void playNextSong(const audio::Song& song);
    void switchBetweenAlbumModes();
    void stepSelection();
    void showHelp();
    void handleAlbumSwitchInAllAlbumMode(bool increase);
    void handleAlbumSwitchInSingleAlbumMode(bool increase);
    void handleAlbumSwitchInMultipleAlbumsMode(bool increase);
    void handleUserInputNumbers(char number);
    void handleDotPressed();
    //TODO: these two functions could be merged into one entity with templates
    void playSongWithDelay(int albumNumber, int songNumber);
    void playAlbumWithDelay(int albumNumber);

    unsigned int getNextVisibleAlbumsIndex(unsigned int currentVisibleAlbumsIndex, bool increase) const;
    unsigned int getNextSelectedAlbumIndex(unsigned int currentSelectedAlbumIndex, bool increase) const;

    jukebox::signals::Slot eventsSlot;
    
    std::unique_ptr<juce::MainComponent> mainComponent;
    std::unique_ptr<MainWindow> mainWindow;

    std::unique_ptr<JukeboxTimer> secondsToPlayTimer;
    
    std::string musicFolder = "";
    std::string userInputSongNumber = "";
    unsigned int visibleAlbumsIndex = 1;
    unsigned int selectedAlbumIndex = 1;
    unsigned int albumIndexStep = 8;
    bool isInMultipleAlbumsMode = true;
};

}}

#endif  // GUI_H_INCLUDED
