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

//[Headers] You can add your own extra header files here...
#include "Logger.h"
#include "Song.h"
#include "JukeboxTimer.h"
#include "MultipleAlbumsCanvas.h"
#include "SingleAlbumCanvas.h"
#include "SetupPage.h"
#include "MusicSetupCanvas.h"
#include "MainComponentPositionCalculator.h"
#include "Password.h"
//[/Headers]

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
namespace {
    constexpr int timeBetweenSongs = 1000;
}

using namespace juce;
using namespace jukebox;
//[/MiscUserDefs]

//==============================================================================
MainComponent::MainComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (infoCredit = new Label ("credits info label",
                                               TRANS("Credits:")));
    infoCredit->setFont (Font (18.00f, Font::plain));
    infoCredit->setJustificationType (Justification::centredLeft);
    infoCredit->setEditable (false, false, false);
    infoCredit->setColour (TextEditor::textColourId, Colours::black);
    infoCredit->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblCredits = new Label ("credits label",
                                               TRANS("0")));
    lblCredits->setFont (Font (32.00f, Font::plain));
    lblCredits->setJustificationType (Justification::centredLeft);
    lblCredits->setEditable (false, false, false);
    lblCredits->setColour (TextEditor::textColourId, Colours::black);
    lblCredits->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblStatus = new Label ("Status label",
                                              TRANS("Ready")));
    lblStatus->setFont (Font (18.00f, Font::plain));
    lblStatus->setJustificationType (Justification::centredLeft);
    lblStatus->setEditable (false, false, false);
    lblStatus->setColour (TextEditor::textColourId, Colours::black);
    lblStatus->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (infoPlayQueue = new Label ("playlist queue info label",
                                                  TRANS("Songs in the queue")));
    infoPlayQueue->setFont (Font (18.00f, Font::plain));
    infoPlayQueue->setJustificationType (Justification::centredLeft);
    infoPlayQueue->setEditable (false, false, false);
    infoPlayQueue->setColour (TextEditor::textColourId, Colours::black);
    infoPlayQueue->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (infoCurrentSong = new Label ("current song info label",
                                                    TRANS("Currently playing:")));
    infoCurrentSong->setFont (Font (18.00f, Font::plain));
    infoCurrentSong->setJustificationType (Justification::centredLeft);
    infoCurrentSong->setEditable (false, false, false);
    infoCurrentSong->setColour (TextEditor::textColourId, Colours::black);
    infoCurrentSong->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtCurrentSong = new TextEditor ("current song text"));
    txtCurrentSong->setMultiLine (true);
    txtCurrentSong->setReturnKeyStartsNewLine (false);
    txtCurrentSong->setReadOnly (true);
    txtCurrentSong->setScrollbarsShown (false);
    txtCurrentSong->setCaretVisible (false);
    txtCurrentSong->setPopupMenuEnabled (true);
    txtCurrentSong->setText (String());

    addAndMakeVisible (multipleAlbumsCanvas = new jukebox::gui::MultipleAlbumsCanvas());
    multipleAlbumsCanvas->setName ("canvas to draw multiple album content");

    addAndMakeVisible (singleAlbumCanvas = new jukebox::gui::SingleAlbumCanvas());
    singleAlbumCanvas->setName ("canvas to draw single album content");

    addAndMakeVisible (lblAlbumNumber = new Label ("show album number user input",
                                                   String()));
    lblAlbumNumber->setFont (Font (32.00f, Font::plain));
    lblAlbumNumber->setJustificationType (Justification::centredLeft);
    lblAlbumNumber->setEditable (false, false, false);
    lblAlbumNumber->setColour (Label::backgroundColourId, Colours::white);
    lblAlbumNumber->setColour (TextEditor::textColourId, Colours::black);
    lblAlbumNumber->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblSongNumber = new Label ("show song number user input",
                                                  String()));
    lblSongNumber->setFont (Font (32.00f, Font::plain));
    lblSongNumber->setJustificationType (Justification::centredLeft);
    lblSongNumber->setEditable (false, false, false);
    lblSongNumber->setColour (Label::backgroundColourId, Colours::white);
    lblSongNumber->setColour (TextEditor::textColourId, Colours::black);
    lblSongNumber->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    singleAlbumCanvas->setVisible(false);
    addAndMakeVisible(listBoxPlayQueue = new jukebox::gui::ListBox<std::deque, jukebox::audio::Song>);

    addChildComponent(setupPage = new jukebox::gui::SetupPage);
    addChildComponent(musicSetupCanvas = new jukebox::gui::MusicSetupCanvas);
    eventsSlot.connect(this, &MainComponent::onMusicDirectoryChanged, musicSetupCanvas->musicDirectoryChangedSignal);
    eventsSlot.connect(this, &MainComponent::onTimeToPlayASongChanged, setupPage->timeToPlayASongChangedSignal);

    //[/UserPreSize]

    //setSize (1400, 800);


    //[Constructor] You can add your own custom stuff here..
    timerBetweenSongs = new jukebox::JukeboxTimer([this](){
        removeCurrentSongImmediately();
    });

    setWantsKeyboardFocus(true);
    grabKeyboardFocus();
    focusInitialised = hasKeyboardFocus(true);
    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lblAlbumNumber = nullptr;
    lblSongNumber = nullptr;
    infoCredit = nullptr;
    lblCredits = nullptr;
    infoCurrentSong = nullptr;
    txtCurrentSong = nullptr;
    infoPlayQueue = nullptr;
    multipleAlbumsCanvas = nullptr;
    singleAlbumCanvas = nullptr;
    setupPage = nullptr;
    musicSetupCanvas = nullptr;
    lblStatus = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    listBoxPlayQueue = nullptr;
    timerBetweenSongs = nullptr;
    //[/Destructor]
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::chocolate);

    //[UserPaint] Add your own custom painting code here..

    if(focusInitialised)
    {
        return;
    }

    if(!hasKeyboardFocus(true))
    {
        grabKeyboardFocus();
        focusInitialised = hasKeyboardFocus(true);

        LOG_INFO("focus set");
    }

    //[/UserPaint]
}

void MainComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]


    //[UserResized] Add your own custom resize handling here..

//    infoCredit->setBounds (1128, 88, 56, 24);
//    lblCredits->setBounds (1192, 88, 32, 24);
//    lblStatus->setBounds (32, 760, 300, 24);
//    infoPlayQueue->setBounds (1128, 240, 150, 24);
//    infoCurrentSong->setBounds (1128, 128, 150, 24);
//    txtCurrentSong->setBounds (1128, 168, 200, 24);
//    multipleAlbumsCanvas->setBounds (32, 32, 1064, 712);
//    lblAlbumNumber->setBounds (1128, 32, 57, 40);
//    lblSongNumber->setBounds (1192, 32, 42, 40);
//    singleAlbumCanvas->setBounds (32, 32, 1064, 712);
//    setupPage->setBounds (32, 32, 1064, 712);
//    listBox->setBounds(1128, 284, 200, 150);
    MainComponentPositionCalculator calc{getWidth(), getHeight()};
    const Font bigFont(calc.getFontHeigthBig(), Font::plain);
    const Font smallFont(calc.getFontHeigthSmall(), Font::plain);
    const auto canvasBounds = calc.getCanvasBounds();

    lblAlbumNumber->setBounds (calc.getLblAlbumNumberBounds());
    lblAlbumNumber->setFont(bigFont);
    lblSongNumber->setBounds (calc.getLblSongNumberBounds());
    lblSongNumber->setFont(bigFont);
    infoCredit->setBounds (calc.getInfoCreditBounds());
    infoCredit->setFont(smallFont);
    lblCredits->setBounds (calc.getLblCreditsBounds());
    lblCredits->setFont(bigFont);
    infoCurrentSong->setBounds (calc.getInfoCurrentSongBounds());
    infoCurrentSong->setFont(smallFont);
    txtCurrentSong->setBounds (calc.getTxtCurrentSongBounds());
    txtCurrentSong->setFont(smallFont);
    infoPlayQueue->setBounds (calc.getInfoPlayQueueBounds());
    infoPlayQueue->setFont(smallFont);
    listBoxPlayQueue->setBounds(calc.getPlayQueueBounds());
    listBoxPlayQueue->setRowHeight(calc.getFontHeigthSmall());
    lblStatus->setBounds (calc.getLblStatusBounds());
    lblStatus->setFont(smallFont);

    multipleAlbumsCanvas->setBounds (canvasBounds);
    singleAlbumCanvas->setBounds (canvasBounds);
    setupPage->setBounds (canvasBounds);
    musicSetupCanvas->setBounds(canvasBounds);
    //[/UserResized]
}

bool MainComponent::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
    keyPressedSignal(key);

    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyPressed]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
MainComponent::MainComponent(bool /*testingConstructor*/)
{
    //do nothing, this is for testing purposes
}

void MainComponent::refreshCredits(unsigned int credits)
{
    lblCredits->setText(String(credits), dontSendNotification);
}

void MainComponent::showStatusMessage(const String& message)
{
    lblStatus->setText(message, dontSendNotification);
}

void MainComponent::loadMultipleAlbums(const std::vector<jukebox::audio::AlbumInfo>& albums, unsigned int firstAlbumIndex)
{
    multipleAlbumsCanvas->loadAlbums(albums, firstAlbumIndex);
}

void MainComponent::loadSingleAlbum(const std::vector<jukebox::audio::AlbumInfo>& albums, unsigned int albumIndex)
{
    singleAlbumCanvas->loadAlbum(albums, albumIndex);
}

void MainComponent::setMusicDirectory(const std::string& musicDirectory)
{
    musicSetupCanvas->setMusicDirectory(musicDirectory);
}

void MainComponent::setTimeToPlayASong(int millisecs)
{
    setupPage->setTimeToPlayASong(millisecs);
}

void MainComponent::setTimeToSaveInsertedCoins(int millisecs)
{
    setupPage->setTimeToSaveInsertedCoins(millisecs);
}

void MainComponent::switchBetweenUserModes()
{
    musicSetupCanvas->setVisible(!musicSetupCanvas->isVisible() && !setupPage->isVisible());
    multipleAlbumsCanvas->setVisible(!musicSetupCanvas->isVisible());
    singleAlbumCanvas->setVisible(false);
    setupPage->setVisible(false);
}

void MainComponent::switchBetweenAlbumViews()
{
    multipleAlbumsCanvas->setVisible(!multipleAlbumsCanvas->isVisible());
    singleAlbumCanvas->setVisible(!singleAlbumCanvas->isVisible());
}

void MainComponent::switchBetweenAdministratorViews()
{
    musicSetupCanvas->setVisible(!musicSetupCanvas->isVisible());
    setupPage->setVisible(!musicSetupCanvas->isVisible());
}

void MainComponent::updateAlbumSelection(unsigned int selectedAlbumIndex)
{
    multipleAlbumsCanvas->setSelection(selectedAlbumIndex);
}

void MainComponent::updateSongSelection(unsigned int selectedSongIndex)
{
    singleAlbumCanvas->setSelection(selectedSongIndex);
}

void MainComponent::setCurrentUserInputNumber(const String& userInput)
{
    lblAlbumNumber->setText(userInput.substring(0, 3), dontSendNotification);
    lblSongNumber->setText(userInput.substring(3), dontSendNotification);
}

void MainComponent::setCurrentlyPlayedSong(const jukebox::audio::Song& song)
{
    txtCurrentSong->setText(song.visibleName);
}

void MainComponent::enqueue(const jukebox::audio::Song& song)
{
    listBoxPlayQueue->insertItem(song);
}

void MainComponent::removeCurrentSong()
{
    showStatusMessage("");
    timerBetweenSongs->runOnce(timeBetweenSongs);
}

void MainComponent::showStatistics(const std::string& statistics)
{
    setupPage->showStatistics(statistics);
}

void MainComponent::removeCurrentSongImmediately()
{
    txtCurrentSong->setText("");

    if(listBoxPlayQueue->hasNextItem())
    {
        const auto nextItem = listBoxPlayQueue->getNextItem();
        listBoxPlayQueue->removeCurrentItem();
        playNextSongSignal(nextItem);
    }
}

void MainComponent::onMusicDirectoryChanged(const std::string& musicDirectory)
{
    musicDirectoryChangedSignal(musicDirectory);
}

void MainComponent::onTimeToPlayASongChanged(int millisecs)
{
    //TODO move?
    timeToPlayASongChangedSignal(std::move(millisecs));
}

void MainComponent::onTimeToSaveInsertedCoinsChanged(int millisecs)
{
    timeToSaveInsertedCoinsChangedSignal(std::move(millisecs));
}

void MainComponent::prepareForExit()
{
    listBoxPlayQueue->clear();
}

bool MainComponent::showPasswordQuestion(const Password& password)
{
    String text("abcdefghijklmnopqrstuvwxyz");
    return password.isMatching(text);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1400" initialHeight="800">
  <METHODS>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffd2691e"/>
  <LABEL name="credits info label" id="b06a2a5d220c224b" memberName="infoCredit"
         virtualName="" explicitFocusOrder="0" pos="1128 88 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Credits:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="credits label" id="559731314e5f9fe6" memberName="lblCredits"
         virtualName="" explicitFocusOrder="0" pos="1192 88 32 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="18"
         bold="0" italic="0" justification="33"/>
  <LABEL name="Status label" id="2888f5d9f29162ec" memberName="lblStatus"
         virtualName="" explicitFocusOrder="0" pos="32 760 300 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Ready" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="playlist queue info label" id="14603449b7b89fe8" memberName="infoPlayQueue"
         virtualName="" explicitFocusOrder="0" pos="1128 240 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Songs in the queue" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="current song info label" id="e2e9b0ce64f022e0" memberName="infoCurrentSong"
         virtualName="" explicitFocusOrder="0" pos="1128 128 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Currently playing:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="current song text" id="e9cd5fc0ca8c98f6" memberName="txtCurrentSong"
              virtualName="" explicitFocusOrder="0" pos="1128 168 200 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="1" scrollbars="0"
              caret="0" popupmenu="1"/>
  <GENERICCOMPONENT name="canvas to draw multiple album content" id="98e3b5ee3d8d0f7b"
                    memberName="multipleAlbumsCanvas" virtualName="" explicitFocusOrder="0"
                    pos="32 32 1064 712" class="jukebox::gui::MultipleAlbumsCanvas"
                    params=""/>
  <GENERICCOMPONENT name="canvas to draw single album content" id="e884540ad76a0310"
                    memberName="singleAlbumCanvas" virtualName="" explicitFocusOrder="0"
                    pos="888 504 302 208" class="jukebox::gui::SingleAlbumCanvas"
                    params=""/>
  <LABEL name="show album number user input" id="2d9fc52c8ca67f72" memberName="lblAlbumNumber"
         virtualName="" explicitFocusOrder="0" pos="1128 32 57 40" bkgCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="32" bold="0" italic="0" justification="33"/>
  <LABEL name="show song number user input" id="393e6ac770590d6d" memberName="lblSongNumber"
         virtualName="" explicitFocusOrder="0" pos="1192 32 42 40" bkgCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="32" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
