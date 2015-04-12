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

private:
    void keyPressed(const KeyPress& key);
    
private:
    jukebox::signals::Slot keyPressedSlot;
    
    std::unique_ptr<MainComponent> mainComponent;
    std::unique_ptr<MainWindow> mainWindow;
};

}}

#endif  // GUI_H_INCLUDED
