#ifndef LISTBOX_HPP_INCLUDED
#define LISTBOX_HPP_INCLUDED

#include "JuceHeader.h"

namespace jukebox { namespace gui {

template<template<class, class> class Container, class Item>
class ListBoxContents : public juce::ListBoxModel
{
public:
    ListBoxContents() = default;
    virtual ~ListBoxContents() = default;
    
    // The following methods implement the necessary virtual functions from ListBoxModel,
    // telling the listbox how many rows there are, painting them, etc.
    int getNumRows() override;

    void paintListBoxItem (int rowNumber, juce::Graphics& g,
                           int width, int height, bool rowIsSelected) override;
                           
    virtual void insertItem(const Item&);
    virtual void removeNextItem();
    virtual Item getNextItem() const;
    virtual int getSize() const;
    
private:
    Container<Item, std::allocator<Item> > items;
};

template<template<class, class> class Container, class Item>
class ListBox : public juce::Component
{
public:
    ListBox();
    virtual ~ListBox() = default;

    void paint (juce::Graphics&) override;
    void resized() override;

    virtual void insertItem(const Item&);
    virtual void removeNextItem();
    virtual Item getNextItem() const;
    virtual int getSize() const;

private:
    juce::ListBox sourceListBox;
    ListBoxContents<Container, Item> sourceModel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ListBox)
};

}}

#include "ListBoxImplementation.hpp"

#endif  // LISTBOX_HPP_INCLUDED
