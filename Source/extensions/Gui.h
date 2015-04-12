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

class ICreditManager;
class MainComponent;
class MainWindow;

class Gui : public IGui
{
public:
    Gui();
    ~Gui();
    
    void initialise(const String& name) override;
    void uninitialise() override;
    
private:
    std::unique_ptr<MainComponent> mainComponent;
    std::unique_ptr<MainWindow> mainWindow;
    
    std::shared_ptr<ICreditManager> creditManager;
};

#endif  // GUI_H_INCLUDED
