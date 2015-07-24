/*
  ==============================================================================

    SongsListBox.cpp
    Created: 2 May 2015 10:15:25am
    Author:  adam

  ==============================================================================
*/

#ifndef LISTBOXIMPLEMENTATION_HPP_INCLUDED
#define LISTBOXIMPLEMENTATION_HPP_INCLUDED

#include "Logger.h"

namespace jukebox { namespace gui {

template<template<class, class> class Container, class Item>
ListBox<Container, Item>::ListBox()
: sourceListBox ("listBox", nullptr)
{
    sourceListBox.setModel (&sourceModel);
    sourceListBox.setMultipleSelectionEnabled (true);

    addAndMakeVisible (sourceListBox);
}

template<template<class, class> class Container, class Item>
void ListBox<Container, Item>::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::lightblue);
    g.setFont (14.0f);
    g.drawText ("SongsListBox", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

template<template<class, class> class Container, class Item>
void ListBox<Container, Item>::insertItem(const Item& item)
{
    sourceModel.insertItem(item);
    sourceListBox.updateContent();
}

template<template<class, class> class Container, class Item>
void ListBox<Container, Item>::removeNextItem()
{
    return sourceModel.removeNextItem();
}

template<template<class, class> class Container, class Item>
Item ListBox<Container, Item>::getNextItem() const
{
    return sourceModel.getNextItem();
}

template<template<class, class> class Container, class Item>
int ListBox<Container, Item>::getSize() const
{
    return sourceModel.getSize();
}

template<template<class, class> class Container, class Item>
void ListBox<Container, Item>::resized()
{
    juce::Rectangle<int> r (getLocalBounds().reduced (8));

    sourceListBox.setBounds (r.withSize (190, 140));
}

template<template<class, class> class Container, class Item>
int ListBoxContents<Container, Item>::getNumRows()
{
    return items.size();
}

template<template<class, class> class Container, class Item>
void ListBoxContents<Container, Item>::paintListBoxItem (int rowNumber, juce::Graphics& g,
                           int width, int height, bool rowIsSelected)
{
    if(rowNumber >= items.size())
    {
        LOG_WARNING("rownumber " << rowNumber << "was greater than the count of elements " << items.size());
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

template<template<class, class> class Container, class Item>
void ListBoxContents<Container, Item>::insertItem(const Item& item)
{
    items.push_back(item);
}

template<template<class, class> class Container, class Item>
void ListBoxContents<Container, Item>::removeNextItem()
{
    items.pop_back();
    LOG_WARNING("called");
}

template<template<class, class> class Container, class Item>
Item ListBoxContents<Container, Item>::getNextItem() const
{
    int size = getSize();
    
    if(size > 0)
    {
        return items[size - 1];
    }
    
    return Item();
}

template<template<class, class> class Container, class Item>
int ListBoxContents<Container, Item>::getSize() const
{
    return items.size();
}

}}

#endif // LISTBOXIMPLEMENTATION_HPP_INCLUDED
