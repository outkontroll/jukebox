/*
  ==============================================================================

    Gui.h
    Created: 14 Mar 2015 3:28:34am
    Author:  adam

  ==============================================================================
*/

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
    Gui();
    ~Gui();
    
    void initialize(const std::string& name) override;
    void uninitialize() override;
    
    void refreshCredits(unsigned int credits) override;
    void showStatusMessage(const std::string& message) override;
    
    void setMusicFolder(const std::string& folder) override;
    
    void enqueue(const std::string& song) override;

private:
    void keyPressed(const juce::KeyPress& key);
    
    void updateAlbumList();
    
private:
    jukebox::signals::Slot keyPressedSlot;
    
    std::unique_ptr<juce::MainComponent> mainComponent;
    std::unique_ptr<MainWindow> mainWindow;
    
    juce::String musicFolder;
    unsigned int position;
};

}}

#endif  // GUI_H_INCLUDED
