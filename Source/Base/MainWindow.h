#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED


#include "JuceHeader.h"

class MainWindow : public juce::ResizableWindow
{
public:
    MainWindow(const juce::String& name, juce::Component* guiComponent);
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
};


#endif  // MAINWINDOW_H_INCLUDED
