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
    class Password;
    class JukeboxTimer;
namespace gui {
    class MultipleAlbumsCanvas;
    class SingleAlbumCanvas;
    class SetupPageCanvas;
    class MusicSetupCanvas;
}
namespace audio {
    struct Song;
    struct AlbumInfo;
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
    ~MainComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    jukebox::signals::Signal<const KeyPress&> keyPressedSignal;
    jukebox::signals::Signal<const jukebox::audio::Song&> playNextSongSignal;
    jukebox::signals::Signal<const std::string&> musicDirectoryChangedSignal;
    jukebox::signals::Signal<int> timeToPlayASongChangedSignal;
    jukebox::signals::Signal<int> timeToSaveInsertedCoinsChangedSignal;
    jukebox::signals::Signal<int> timeToPlayAdvertiseMusicChangedSignal;
    jukebox::signals::Signal<const jukebox::Password&> passwordChangedSignal;
    jukebox::signals::Signal<> passwordTurnedOffSignal;
    jukebox::signals::Signal<const std::string&> requestToImportAlbumSignal;
    //the virtuals are here only to enable easier testing and mocking

    virtual void refreshCredits(unsigned int credits);
    virtual void showStatusMessage(const String& message);
    virtual void loadMultipleAlbums(const std::vector<jukebox::audio::AlbumInfo>& albums, unsigned int firstAlbumIndex);
    virtual void loadSingleAlbum(const std::vector<jukebox::audio::AlbumInfo>& albums, unsigned int albumIndex);
    virtual void setMusicDirectory(const std::string& musicDirectory);
    virtual void setAlbumsForMusicSetup(const std::vector<jukebox::audio::AlbumInfo>& albums);
    virtual void setTimeToPlayASong(int millisecs);
    virtual void setTimeToSaveInsertedCoins(int millisecs);
    virtual void setTimeToPlayAdvertiseMusic(int millisecs);
    virtual void setPassword(const jukebox::Password* password);
    virtual void turnOffPassword();
    virtual void switchBetweenUserModes();
    virtual void switchBetweenAlbumViews();
    virtual void switchBetweenAdministratorViews();
    virtual void updateAlbumSelection(unsigned int selectedAlbumIndex);
    virtual void updateSongSelection(unsigned int selectedSongIndex);
    virtual void setCurrentUserInputNumber(const String& userInput);
    virtual void setCurrentlyPlayedSong(const jukebox::audio::Song& song);
    virtual void enqueue(const jukebox::audio::Song &song);
    virtual void removeCurrentSong();
    virtual void showStatistics(const std::string& statistics);
    virtual void prepareForExit();

    virtual bool showPasswordQuestion();
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
    void onMusicDirectoryChanged(const std::string& musicDirectory);
    void onTimeToPlayASongChanged(int);
    void onTimeToSaveInsertedCoinsChanged(int);
    void onTimeToPlayAdvertiseMusicChanged(int);
    void onPasswordChanged(const jukebox::Password& password);
    void onPasswordTurnedOff();
    void onRequestToImportAlbumSignal(const std::string& albumToImport);
    void grabFocus();

    ScopedPointer<jukebox::gui::ListBox<std::deque, jukebox::audio::Song>> listBoxPlayQueue;
    ScopedPointer<jukebox::JukeboxTimer> timerBetweenSongs;
    bool focusInitialised;
    const jukebox::Password* password = nullptr;
    jukebox::signals::Slot eventsSlot;
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
    ScopedPointer<jukebox::gui::SetupPageCanvas> setupPage;
    ScopedPointer<jukebox::gui::MusicSetupCanvas> musicSetupCanvas;
    ScopedPointer<Label> lblAlbumNumber;
    ScopedPointer<Label> lblSongNumber;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

//[EndFile] You can add extra defines here...
}
//[/EndFile]

#endif   // __JUCE_HEADER_9002020A4DD09B20__
