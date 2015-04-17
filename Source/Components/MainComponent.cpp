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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//using namespace jukebox::signals;
//[/MiscUserDefs]

//==============================================================================
MainComponent::MainComponent ()
{
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
    txtAlbumList->setMultiLine (false);
    txtAlbumList->setReturnKeyStartsNewLine (false);
    txtAlbumList->setReadOnly (false);
    txtAlbumList->setScrollbarsShown (true);
    txtAlbumList->setCaretVisible (true);
    txtAlbumList->setPopupMenuEnabled (true);
    txtAlbumList->setColour (TextEditor::backgroundColourId, Colour (0xffdadada));
    txtAlbumList->setText (String::empty);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


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


    //[Destructor]. You can add your own custom destruction code here..
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
    }

    //[/UserPaint]
}

void MainComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    infoCredit->setBounds (8, 8, 56, 24);
    lblCredits->setBounds (72, 8, 32, 24);
    lblStatus->setBounds (16, 272, 150, 24);
    txtAlbumList->setBounds (16, 48, 136, 216);
    //[UserResized] Add your own custom resize handling here..
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
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <METHODS>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="credits info label" id="b06a2a5d220c224b" memberName="infoCredit"
         virtualName="" explicitFocusOrder="0" pos="8 8 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Credits:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="credits label" id="559731314e5f9fe6" memberName="lblCredits"
         virtualName="" explicitFocusOrder="0" pos="72 8 32 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="18"
         bold="0" italic="0" justification="33"/>
  <LABEL name="Status label" id="2888f5d9f29162ec" memberName="lblStatus"
         virtualName="" explicitFocusOrder="0" pos="16 272 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Ready" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="List of albums" id="c309162dc4be8cd5" memberName="txtAlbumList"
              virtualName="" explicitFocusOrder="0" pos="16 48 136 216" bkgcol="ffdadada"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="1" caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
