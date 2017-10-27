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
//[/Headers]

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
using namespace juce;
//[/MiscUserDefs]

//==============================================================================
MainComponent::MainComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (infoCredit = new Label ("credits info label",
                                               TRANS("Credits:")));
    infoCredit->setFont (Font (15.00f, Font::plain));
    infoCredit->setJustificationType (Justification::centredLeft);
    infoCredit->setEditable (false, false, false);
    infoCredit->setColour (TextEditor::textColourId, Colours::black);
    infoCredit->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblCredits = new Label ("credits label",
                                               TRANS("0")));
    lblCredits->setFont (Font (18.00f, Font::plain));
    lblCredits->setJustificationType (Justification::centredLeft);
    lblCredits->setEditable (false, false, false);
    lblCredits->setColour (TextEditor::textColourId, Colours::black);
    lblCredits->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblStatus = new Label ("Status label",
                                              TRANS("Ready")));
    lblStatus->setFont (Font (15.00f, Font::plain));
    lblStatus->setJustificationType (Justification::centredLeft);
    lblStatus->setEditable (false, false, false);
    lblStatus->setColour (TextEditor::textColourId, Colours::black);
    lblStatus->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtAlbumList = new TextEditor ("List of albums"));
    txtAlbumList->setMultiLine (true);
    txtAlbumList->setReturnKeyStartsNewLine (false);
    txtAlbumList->setReadOnly (true);
    txtAlbumList->setScrollbarsShown (true);
    txtAlbumList->setCaretVisible (false);
    txtAlbumList->setPopupMenuEnabled (true);
    txtAlbumList->setColour (TextEditor::backgroundColourId, Colour (0xffdadada));
    txtAlbumList->setText (String());

    addAndMakeVisible (infoPlayQueue = new Label ("playlist queue info label",
                                                  TRANS("Songs in the queue")));
    infoPlayQueue->setFont (Font (15.00f, Font::plain));
    infoPlayQueue->setJustificationType (Justification::centredLeft);
    infoPlayQueue->setEditable (false, false, false);
    infoPlayQueue->setColour (TextEditor::textColourId, Colours::black);
    infoPlayQueue->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (infoCurrentSong = new Label ("current song info label",
                                                    TRANS("Currently playing:")));
    infoCurrentSong->setFont (Font (15.00f, Font::plain));
    infoCurrentSong->setJustificationType (Justification::centredLeft);
    infoCurrentSong->setEditable (false, false, false);
    infoCurrentSong->setColour (TextEditor::textColourId, Colours::black);
    infoCurrentSong->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtCurrentSong = new TextEditor ("current song text"));
    txtCurrentSong->setMultiLine (false);
    txtCurrentSong->setReturnKeyStartsNewLine (false);
    txtCurrentSong->setReadOnly (true);
    txtCurrentSong->setScrollbarsShown (true);
    txtCurrentSong->setCaretVisible (false);
    txtCurrentSong->setPopupMenuEnabled (true);
    txtCurrentSong->setText (String());

    addAndMakeVisible (multipleAlbumsCanvas = new jukebox::gui::MultipleAlbumsCanvas());
    multipleAlbumsCanvas->setName ("canvas to draw multiple album content");

    addAndMakeVisible (singleAlbumCanvas = new jukebox::gui::SingleAlbumCanvas());
    singleAlbumCanvas->setName ("canvas to draw single album content");


    //[UserPreSize]
    txtAlbumList->setVisible(false);
    singleAlbumCanvas->setVisible(false);

    addAndMakeVisible (listBox = new jukebox::gui::ListBox<std::deque, jukebox::audio::Song>);
    //[/UserPreSize]

    setSize (1400, 800);


    //[Constructor] You can add your own custom stuff here..
    number = 0;
    setWantsKeyboardFocus(true);
    grabKeyboardFocus();
    focusInitialised = hasKeyboardFocus(true);
    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    infoCredit = nullptr;
    lblCredits = nullptr;
    lblStatus = nullptr;
    txtAlbumList = nullptr;
    infoPlayQueue = nullptr;
    infoCurrentSong = nullptr;
    txtCurrentSong = nullptr;
    multipleAlbumsCanvas = nullptr;
    singleAlbumCanvas = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    listBox = nullptr;
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

    infoCredit->setBounds (1128, 32, 56, 24);
    lblCredits->setBounds (1192, 32, 32, 24);
    lblStatus->setBounds (32, 760, 300, 24);
    txtAlbumList->setBounds (32, 32, 272, 216);
    infoPlayQueue->setBounds (1128, 184, 150, 24);
    infoCurrentSong->setBounds (1128, 72, 150, 24);
    txtCurrentSong->setBounds (1128, 112, 200, 24);
    multipleAlbumsCanvas->setBounds (32, 32, 1064, 712);
    singleAlbumCanvas->setBounds (32, 32, 1064, 712);
    //[UserResized] Add your own custom resize handling here..
    //singleAlbumCanvas->setBounds(multipleAlbumsCanvas->getBounds());
    listBox->setBounds(1128, 228, 200, 150);
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
void MainComponent::refreshCredits(unsigned int credits)
{
    lblCredits->setText(String(credits), dontSendNotification);
}

void MainComponent::showStatusMessage(const String& message)
{
    lblStatus->setText(message, dontSendNotification);
}

void MainComponent::updateAlbumList(const String& albumList)
{
    txtAlbumList->setText(albumList);
}

void MainComponent::loadMultipleAlbums(const std::string& musicDirectory, int firstAlbumIndex)
{
    multipleAlbumsCanvas->loadAlbums(musicDirectory, firstAlbumIndex);
}

void MainComponent::loadSingleAlbum(const std::string& musicDirectory, int albumIndex)
{
    singleAlbumCanvas->loadAlbum(musicDirectory, albumIndex);
}

void MainComponent::switchBetweenAlbumViews()
{
    multipleAlbumsCanvas->setVisible(!multipleAlbumsCanvas->isVisible());
    singleAlbumCanvas->setVisible(!singleAlbumCanvas->isVisible());
}

void MainComponent::updateSelection(int selectedAlbumIndex)
{
    multipleAlbumsCanvas->setSelection(selectedAlbumIndex);
}

void MainComponent::setCurrentlyPlayedSong(const jukebox::audio::Song& song)
{
    txtCurrentSong->setText(song.toString());
}

void MainComponent::enqueue(const jukebox::audio::Song& song)
{
    listBox->insertItem(song);
}

void MainComponent::removeCurrentSong()
{
    txtCurrentSong->setText("");

    if(listBox->hasNextItem())
    {
        auto nextItem = listBox->getNextItem();
        listBox->removeCurrentItem();
        playNextSongSignal(nextItem);
    }
}

void MainComponent::prepareForExit()
{
    listBox->clear();
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
         virtualName="" explicitFocusOrder="0" pos="1128 32 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Credits:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="credits label" id="559731314e5f9fe6" memberName="lblCredits"
         virtualName="" explicitFocusOrder="0" pos="1192 32 32 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="18"
         bold="0" italic="0" justification="33"/>
  <LABEL name="Status label" id="2888f5d9f29162ec" memberName="lblStatus"
         virtualName="" explicitFocusOrder="0" pos="32 760 300 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Ready" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="List of albums" id="c309162dc4be8cd5" memberName="txtAlbumList"
              virtualName="" explicitFocusOrder="0" pos="32 32 272 216" bkgcol="ffdadada"
              initialText="" multiline="1" retKeyStartsLine="0" readonly="1"
              scrollbars="1" caret="0" popupmenu="1"/>
  <LABEL name="playlist queue info label" id="14603449b7b89fe8" memberName="infoPlayQueue"
         virtualName="" explicitFocusOrder="0" pos="1128 184 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Songs in the queue" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="current song info label" id="e2e9b0ce64f022e0" memberName="infoCurrentSong"
         virtualName="" explicitFocusOrder="0" pos="1128 72 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Currently playing:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="current song text" id="e9cd5fc0ca8c98f6" memberName="txtCurrentSong"
              virtualName="" explicitFocusOrder="0" pos="1128 112 200 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="1" scrollbars="1"
              caret="0" popupmenu="1"/>
  <GENERICCOMPONENT name="canvas to draw multiple album content" id="98e3b5ee3d8d0f7b"
                    memberName="multipleAlbumsCanvas" virtualName="" explicitFocusOrder="0"
                    pos="32 32 1064 712" class="jukebox::gui::MultipleAlbumsCanvas"
                    params=""/>
  <GENERICCOMPONENT name="canvas to draw single album content" id="e884540ad76a0310"
                    memberName="singleAlbumCanvas" virtualName="" explicitFocusOrder="0"
                    pos="888 504 302 208" class="jukebox::gui::SingleAlbumCanvas"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
