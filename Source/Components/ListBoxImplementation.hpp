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
    
    //without this call the changes would not be visible
    repaint();
}

template<template<class, class> class Container, class Item>
bool ListBox<Container, Item>::hasNextItem() const
{
    return sourceModel.hasNextItem();
}

template<template<class, class> class Container, class Item>
void ListBox<Container, Item>::removeCurrentItem()
{
    sourceModel.removeCurrentItem();
    
    //without this call the changes would not be visible
    repaint();
}

template<template<class, class> class Container, class Item>
Item ListBox<Container, Item>::getNextItem() const
{
    return sourceModel.getNextItem();
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
    if(rowNumber < 0 || static_cast<unsigned>(rowNumber) >= items.size())
    {
        //TODO check if a warning is needed
        //LOG_WARNING("row #" << rowNumber << " was out of range, count of elements: " << items.size() << ", capacity: " << items.capacity());
        return;
    }
    
    if(rowIsSelected)
    {
        g.fillAll (juce::Colours::lightblue);
    }
    
    g.setColour (juce::Colours::black);
    g.setFont (height * 0.7f);

    g.drawText (items[rowNumber].toString(), 5, 0, width, height,
                juce::Justification::centredLeft, true);
}

template<template<class, class> class Container, class Item>
void ListBoxContents<Container, Item>::insertItem(const Item& item)
{
    items.push_back(item);
}

template<template<class, class> class Container, class Item>
bool ListBoxContents<Container, Item>::hasNextItem() const
{
    return items.size() > 0;
}

template<template<class, class> class Container, class Item>
void ListBoxContents<Container, Item>::removeCurrentItem()
{
    if(items.size() > 0)
    {
        items.pop_front();
    }
    else
    {
        LOG_WARNING("There are no items in the listbox!");
    }
}

template<template<class, class> class Container, class Item>
Item ListBoxContents<Container, Item>::getNextItem() const
{
    if(items.size() > 0)
    {
        return items[0];
    }

    return Item();
}

}}

#endif // LISTBOXIMPLEMENTATION_HPP_INCLUDED
