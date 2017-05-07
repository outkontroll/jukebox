#ifndef LISTBOX_HPP_INCLUDED
#define LISTBOX_HPP_INCLUDED

#include "JuceHeader.h"

namespace jukebox { namespace gui {

template<class Item>
class IListBox
{
public:
    virtual ~IListBox() = default;

    virtual void insertItem(const Item&) = 0;
    virtual bool hasNextItem() const = 0;
    virtual void removeNextItem() = 0;
    virtual Item getNextItem() const = 0;
    virtual int getSize() const = 0;
};

template<template<class, class> class Container, class Item>
class ListBoxContents : public juce::ListBoxModel, private IListBox<Item>
{
public:
    ListBoxContents() = default;
    virtual ~ListBoxContents() = default;
    
    // The following methods implement the necessary virtual functions from ListBoxModel,
    // telling the listbox how many rows there are, painting them, etc.
    int getNumRows() override;

    void paintListBoxItem (int rowNumber, juce::Graphics& g,
                           int width, int height, bool rowIsSelected) override;
                           
    void insertItem(const Item&) override;
    bool hasNextItem() const override;
    void removeNextItem() override;
    Item getNextItem() const override;
    int getSize() const override;
    
private:
    Container<Item, std::allocator<Item> > items;
};

template<template<class, class> class Container, class Item>
class ListBox : public juce::Component, private IListBox<Item>
{
public:
    ListBox();
    virtual ~ListBox() = default;

    void paint (juce::Graphics&) override;
    void resized() override;

    void insertItem(const Item&) override;
    bool hasNextItem() const override;
    void removeNextItem() override;
    Item getNextItem() const override;
    int getSize() const override;

private:
    juce::ListBox sourceListBox;
    ListBoxContents<Container, Item> sourceModel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ListBox)
};

}}

#include "ListBoxImplementation.hpp"

#endif  // LISTBOX_HPP_INCLUDED
