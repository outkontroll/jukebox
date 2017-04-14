#include "MainWindow.h"

using namespace juce;

MainWindow::MainWindow(const String& name, Component* guiComponent)
 : ResizableWindow(name, true)
{
    setContentNonOwned(guiComponent, true);
    
    centreWithSize(getWidth(), getHeight());
    setVisible(true);
}
