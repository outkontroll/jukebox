#ifndef LISTBOXIMPLEMENTATION_HPP_INCLUDED
#define LISTBOXIMPLEMENTATION_HPP_INCLUDED

#include "Logger.h"
#include <cassert>

namespace jukebox { namespace gui {

template<template<class, class> class Container, class Item>
ListBox<Container, Item>::ListBox()
: sourceListBox ("listBox", nullptr)
{
    sourceListBox.setModel (&sourceModel);

    addAndMakeVisible (sourceListBox);
}

template<template<class, class> class Container, class Item>
void ListBox<Container, Item>::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);   // clear the background

    g.setColour (juce::Colours::grey);
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
bool ListBox<Container, Item>::hasNextItem() const noexcept
{
    return sourceModel.hasNextItem();
}

template<template<class, class> class Container, class Item>
void ListBox<Container, Item>::removeCurrentItem()
{
    sourceModel.removeCurrentItem();
    sourceListBox.updateContent();
    
    //without this call the changes would not be visible
    repaint();
}

template<template<class, class> class Container, class Item>
Item ListBox<Container, Item>::getNextItem() const
{
    return sourceModel.getNextItem();
}

template<template<class, class> class Container, class Item>
void ListBox<Container, Item>::clear() noexcept
{
    sourceModel.clear();
}

template<template<class, class> class Container, class Item>
void ListBox<Container, Item>::setRowHeight(int height)
{
    sourceListBox.setRowHeight(height);
}

template<template<class, class> class Container, class Item>
void ListBox<Container, Item>::resized()
{
    sourceListBox.setBounds(getLocalBounds());
}

template<template<class, class> class Container, class Item>
int ListBoxContents<Container, Item>::getNumRows()
{
    return static_cast<int>(items.size());
}

template<template<class, class> class Container, class Item>
void ListBoxContents<Container, Item>::paintListBoxItem (int rowNumber, juce::Graphics& g,
                           int width, int height, bool rowIsSelected)
{
    if(rowNumber < 0 || static_cast<unsigned>(rowNumber) >= items.size())
    {
        return;
    }
    
    if(rowIsSelected)
    {
        g.fillAll (juce::Colours::lightblue);
    }
    
    g.setColour (juce::Colours::black);
    g.setFont (height * 0.9f);

    g.drawText (items[static_cast<unsigned>(rowNumber)].visibleName, 5, 0, width, height, juce::Justification::centredLeft, true);
}

template<template<class, class> class Container, class Item>
void ListBoxContents<Container, Item>::insertItem(const Item& item)
{
    items.emplace_back(item);
}

template<template<class, class> class Container, class Item>
bool ListBoxContents<Container, Item>::hasNextItem() const noexcept
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
    assert(items.size() > 0);
    return items[0];
}

template<template<class, class> class Container, class Item>
void ListBoxContents<Container, Item>::clear() noexcept
{
    items.clear();
}

}}

#endif // LISTBOXIMPLEMENTATION_HPP_INCLUDED
