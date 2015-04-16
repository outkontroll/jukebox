/*
  ==============================================================================

    Gui.h
    Created: 14 Mar 2015 3:28:34am
    Author:  adam

  ==============================================================================
*/

#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include "IGui.h"
#include <memory>

class MainComponent;
class MainWindow;

namespace jukebox { namespace gui {

class Gui : public IGui
{
public:
    Gui();
    ~Gui();
    
    void initialise(const String& name) override;
    void uninitialise() override;
    
    void refreshCredits(unsigned int credits) override;
    void showStatusMessage(const String& message) override;
    
    void setMusicFolder(const String& folder) override;

private:
    void keyPressed(const KeyPress& key);
    
    void updateAlbumList();
    
private:
    jukebox::signals::Slot keyPressedSlot;
    
    std::unique_ptr<MainComponent> mainComponent;
    std::unique_ptr<MainWindow> mainWindow;
    
    String musicFolder;
    unsigned int position;
};

}}

#endif  // GUI_H_INCLUDED
