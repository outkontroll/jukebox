#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include "JuceHeader.h"
#include "IGui.h"
#include <memory>

namespace juce {
    class MainComponent;
}

class MainWindow;

namespace jukebox { namespace gui {

class Gui : public IGui
{
public:
    Gui(const std::string& name);
    //TODO: check why is the = default one wrong
    ~Gui();

    void playNextSong(const audio::Song& song);

    void refreshCredits(unsigned int credits) override;
    void showStatusMessage(const std::string& message) override;
    
    void setMusicFolder(const std::string& folder) override;
    
    void enqueue(const audio::Song& song) override;
    void removeCurrentSong() override;
    
private:
    void keyPressed(const juce::KeyPress& key);
    
    void updateAlbumList();
    void showHelp();

    jukebox::signals::Slot eventsSlot;
    
    std::unique_ptr<juce::MainComponent> mainComponent;
    std::unique_ptr<MainWindow> mainWindow;
    
    juce::String musicFolder;
    unsigned int position;
};

}}

#endif  // GUI_H_INCLUDED
