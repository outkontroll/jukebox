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
jukebox::gui::ListBox::ListBox()
: sourceListBox ("listBox", nullptr)
{
    sourceListBox.setModel (&sourceModel);
    sourceListBox.setMultipleSelectionEnabled (true);

    addAndMakeVisible (sourceListBox);
}

void jukebox::gui::ListBox::paint (Graphics& g)
{
    g.fillAll (Colours::white);   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::lightblue);
    g.setFont (14.0f);
    g.drawText ("SongsListBox", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void jukebox::gui::ListBox::insertItem(const std::string& item)
{
    sourceModel.insertItem(item);
    sourceListBox.updateContent();
}

void jukebox::gui::ListBox::resized()
{
    Rectangle<int> r (getLocalBounds().reduced (8));

    sourceListBox.setBounds (r.withSize (190, 140));
}

int jukebox::gui::ListBoxContents::getNumRows()
{
    return items.size();
}

void jukebox::gui::ListBoxContents::paintListBoxItem (int rowNumber, juce::Graphics& g,
                           int width, int height, bool rowIsSelected)
{
    if(rowNumber >= items.size())
    {
        return;
    }
    
    if (rowIsSelected)
    {
        g.fillAll (juce::Colours::lightblue);
    }
    
    g.setColour (juce::Colours::black);
    g.setFont (height * 0.7f);

    g.drawText (items[rowNumber], 5, 0, width, height,
                juce::Justification::centredLeft, true);
}
    
void jukebox::gui::ListBoxContents::insertItem(const std::string& item)
{
    items.push_back(item);
}

