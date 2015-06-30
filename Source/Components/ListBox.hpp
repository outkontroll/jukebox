/*
  ==============================================================================

    SongsListBox.h
    Created: 2 May 2015 10:15:25am
    Author:  adam

  ==============================================================================
*/

#ifndef SONGSLISTBOX_HPP_INCLUDED
#define SONGSLISTBOX_HPP_INCLUDED

#include "JuceHeader.h"

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
    
private:
    Container<Item, std::allocator<Item> > items;
};

template<template<class, class> class Container, class Item>
class ListBox : public juce::Component
{
public:
    ListBox();

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void insertItem(const Item&);
    
    //TODO: insert, remove, getRowNumber functions

private:
    juce::ListBox sourceListBox;
    ListBoxContents<Container, Item> sourceModel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ListBox)
};

}}

#include "ListBoxImplementation.hpp"

#endif  // SONGSLISTBOX_HPP_INCLUDED
