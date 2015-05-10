/*
  ==============================================================================

    SongsListBox.cpp
    Created: 2 May 2015 10:15:25am
    Author:  adam

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "SongsListBox.h"

using namespace juce;

//==============================================================================
SongsListBox::SongsListBox()
: sourceListBox ("D+D source", nullptr)
{
    sourceListBox.setModel (&sourceModel);
    sourceListBox.setMultipleSelectionEnabled (true);

    addAndMakeVisible (sourceListBox);
}

SongsListBox::~SongsListBox()
{
}

void SongsListBox::paint (Graphics& g)
{
    g.fillAll (Colours::white);   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::lightblue);
    g.setFont (14.0f);
    g.drawText ("SongsListBox", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void SongsListBox::resized()
{
    Rectangle<int> r (getLocalBounds().reduced (8));

    sourceListBox.setBounds (r.withSize (190, 140));
}
