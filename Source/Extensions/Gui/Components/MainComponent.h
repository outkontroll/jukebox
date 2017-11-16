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
#include "Signals.hpp"
#include <string>
#include <deque>

namespace jukebox {
namespace gui {
    class JukeboxTimer;
    class MultipleAlbumsCanvas;
    class SingleAlbumCanvas;
}
namespace audio {
    struct Song;
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

    //the virtuals are here only to enable easier testing and mocking
    //TODO should reconsider the class because of this

    virtual void refreshCredits(unsigned int credits);
    virtual void showStatusMessage(const String& message);
    virtual void loadMultipleAlbums(const std::string& musicDirectory, int firstAlbumIndex);
    virtual void loadSingleAlbum(const std::string& musicDirectory, int albumIndex);
    virtual void switchBetweenAlbumViews();
    virtual void updateSelection(int selectedAlbumIndex);
    virtual void setCurrentUserInputNumber(const String& userInput);
    virtual void setCurrentlyPlayedSong(const jukebox::audio::Song& song);
    virtual void enqueue(const jukebox::audio::Song &song);
    virtual void removeCurrentSong();
    virtual void prepareForExit();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    bool keyPressed (const KeyPress& key) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
protected:
    //this constructor is for testing purposes only to avoid segmentation fault in mocked tests
    MainComponent(bool testingConstructor);

private:
    void removeCurrentSongImmediately();

    ScopedPointer<jukebox::gui::ListBox<std::deque, jukebox::audio::Song>> listBox;
    ScopedPointer<jukebox::gui::JukeboxTimer> timerBetweenSongs;
    bool focusInitialised;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> infoCredit;
    ScopedPointer<Label> lblCredits;
    ScopedPointer<Label> lblStatus;
    ScopedPointer<Label> infoPlayQueue;
    ScopedPointer<Label> infoCurrentSong;
    ScopedPointer<TextEditor> txtCurrentSong;
    ScopedPointer<jukebox::gui::MultipleAlbumsCanvas> multipleAlbumsCanvas;
    ScopedPointer<jukebox::gui::SingleAlbumCanvas> singleAlbumCanvas;
    ScopedPointer<Label> lblAlbumNumber;
    ScopedPointer<Label> lblSongNumber;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

//[EndFile] You can add extra defines here...
}
//[/EndFile]

#endif   // __JUCE_HEADER_9002020A4DD09B20__
