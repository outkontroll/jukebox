/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_9002020A4DD09B20__
#define __JUCE_HEADER_9002020A4DD09B20__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "SongsListBox.h"
#include "Signals.hpp"

namespace juce {
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainComponent  : public Component
{
public:
    //==============================================================================
    MainComponent ();
    ~MainComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    jukebox::signals::Signal<const KeyPress&> keyPressedSignal;

    void refreshCredits(unsigned int credits);
    void showStatusMessage(const String& message);
    void updateAlbumList(const String& albumList);
    void enqueue(const std::string& song);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    bool keyPressed (const KeyPress& key);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ScopedPointer<SongsListBox> listBox;
    unsigned int number;
    bool focusInitialised;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> infoCredit;
    ScopedPointer<Label> lblCredits;
    ScopedPointer<Label> lblStatus;
    ScopedPointer<TextEditor> txtAlbumList;
    ScopedPointer<Label> infoPlayQueue;
    ScopedPointer<Label> infoCurrentSong;
    ScopedPointer<TextEditor> txtCurrentSong;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

//[EndFile] You can add extra defines here...
}
//[/EndFile]

#endif   // __JUCE_HEADER_9002020A4DD09B20__
