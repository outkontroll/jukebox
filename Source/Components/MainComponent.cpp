/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.1

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "Logger.h"
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
    txtAlbumList->setText (String::empty);

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
    txtCurrentSong->setText (String::empty);


    //[UserPreSize]
    addAndMakeVisible (listBox = new jukebox::gui::ListBox<std::vector, std::string>);
    //[/UserPreSize]

    setSize (1000, 650);


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


    //[Destructor]. You can add your own custom destruction code here..
    listBox = nullptr;
    //[/Destructor]
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..

    if(focusInitialised)
    {
        return;
    }

    if( ! hasKeyboardFocus(true))
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

    infoCredit->setBounds (728, 24, 56, 24);
    lblCredits->setBounds (792, 24, 32, 24);
    lblStatus->setBounds (32, 560, 150, 24);
    txtAlbumList->setBounds (32, 24, 272, 216);
    infoPlayQueue->setBounds (728, 176, 150, 24);
    infoCurrentSong->setBounds (728, 64, 150, 24);
    txtCurrentSong->setBounds (728, 104, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    listBox->setBounds(728, 220, 200, 150);
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

void MainComponent::enqueue(const std::string& song)
{
    listBox->insertItem(song);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1000" initialHeight="650">
  <METHODS>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="credits info label" id="b06a2a5d220c224b" memberName="infoCredit"
         virtualName="" explicitFocusOrder="0" pos="728 24 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Credits:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="credits label" id="559731314e5f9fe6" memberName="lblCredits"
         virtualName="" explicitFocusOrder="0" pos="792 24 32 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="18"
         bold="0" italic="0" justification="33"/>
  <LABEL name="Status label" id="2888f5d9f29162ec" memberName="lblStatus"
         virtualName="" explicitFocusOrder="0" pos="32 560 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Ready" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="List of albums" id="c309162dc4be8cd5" memberName="txtAlbumList"
              virtualName="" explicitFocusOrder="0" pos="32 24 272 216" bkgcol="ffdadada"
              initialText="" multiline="1" retKeyStartsLine="0" readonly="1"
              scrollbars="1" caret="0" popupmenu="1"/>
  <LABEL name="playlist queue info label" id="14603449b7b89fe8" memberName="infoPlayQueue"
         virtualName="" explicitFocusOrder="0" pos="728 176 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Songs in the queue" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="current song info label" id="e2e9b0ce64f022e0" memberName="infoCurrentSong"
         virtualName="" explicitFocusOrder="0" pos="728 64 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Currently playing:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="current song text" id="e9cd5fc0ca8c98f6" memberName="txtCurrentSong"
              virtualName="" explicitFocusOrder="0" pos="728 104 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="1" scrollbars="1"
              caret="0" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
