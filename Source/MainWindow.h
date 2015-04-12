/*
  ==============================================================================

    MainWindow.h
    Created: 15 Mar 2015 2:56:27pm
    Author:  adam

  ==============================================================================
*/

#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED


#include "JuceHeader.h"

class MainWindow : public ResizableWindow
{
public:
    MainWindow(const String& name, Component* guiComponent);
    ~MainWindow();
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow);
};


#endif  // MAINWINDOW_H_INCLUDED
