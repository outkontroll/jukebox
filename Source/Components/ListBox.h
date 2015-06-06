/*
  ==============================================================================

    SongsListBox.h
    Created: 2 May 2015 10:15:25am
    Author:  adam

  ==============================================================================
*/

#ifndef SONGSLISTBOX_H_INCLUDED
#define SONGSLISTBOX_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"
#include <string>
#include <deque>
#include <vector>

//==============================================================================
/*
*/

namespace jukebox { namespace gui {

template<template<class, class> class Container, class Item>
class ListBoxContents : public juce::ListBoxModel
{
public:
    // The following methods implement the necessary virtual functions from ListBoxModel,
    // telling the listbox how many rows there are, painting them, etc.
    int getNumRows() override;

    void paintListBoxItem (int rowNumber, juce::Graphics& g,
                           int width, int height, bool rowIsSelected) override;
                           
    void insertItem(const Item&);
    //std::string getItem(unsigned int) const;
    
private:
    //std::deque<Item> items;
    Container<Item, std::allocator<Item> > items;
};

class ListBox : public juce::Component
{
public:
    ListBox();

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void insertItem(const std::string&);
    
    //TODO: insert, remove, getRowNumber functions

private:
    juce::ListBox sourceListBox;
    ListBoxContents</*std::deque*/std::vector, std::string> sourceModel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ListBox)
};

}}

#endif  // SONGSLISTBOX_H_INCLUDED
