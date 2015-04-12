/*
  ==============================================================================

    MainWindow.cpp
    Created: 15 Mar 2015 2:56:27pm
    Author:  adam

  ==============================================================================
*/

#include "MainWindow.h"

MainWindow::MainWindow(const String& name, Component* guiComponent)
 : ResizableWindow(name, true)
{
    setContentNonOwned(guiComponent, true);
    
    centreWithSize(getWidth(), getHeight());
    setVisible(true);
}

MainWindow::~MainWindow()
{
}
