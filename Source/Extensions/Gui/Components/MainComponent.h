/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_9002020A4DD09B20__
#define __JUCE_HEADER_9002020A4DD09B20__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "ListBox.hpp"
#include "MultipleAlbumsCanvas.h"
#include "SingleAlbumCanvas.h"
#include "Signals.hpp"
#include <string>
#include <deque>

namespace jukebox { namespace audio {
    class Song;
}}

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
    jukebox::signals::Signal<const jukebox::audio::Song&> playNextSongSignal;

    void refreshCredits(unsigned int credits);
    void showStatusMessage(const String& message);
    //TODO
    void updateAlbumList(const String& albumList);
    //END TODO
    void loadAlbums(const std::string& musicDirectory, int firstAlbumIndex);
    void switchBetweenAlbumViews();
    void setCurrentlyPlayedSong(const jukebox::audio::Song& song);
    void enqueue(const jukebox::audio::Song &song);
    void removeCurrentSong();
    void prepareForExit();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    bool keyPressed (const KeyPress& key) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ScopedPointer<jukebox::gui::ListBox<std::deque, jukebox::audio::Song>> listBox;
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
    ScopedPointer<jukebox::gui::MultipleAlbumsCanvas> multipleAlbumsCanvas;
    ScopedPointer<jukebox::gui::SingleAlbumCanvas> singleAlbumCanvas;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

//[EndFile] You can add extra defines here...
}
//[/EndFile]

#endif   // __JUCE_HEADER_9002020A4DD09B20__
