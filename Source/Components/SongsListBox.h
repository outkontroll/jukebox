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

//==============================================================================
/*
*/

struct SongListBoxContents  : public juce::ListBoxModel
{
    // The following methods implement the necessary virtual functions from ListBoxModel,
    // telling the listbox how many rows there are, painting them, etc.
    int getNumRows() override
    {
        //TODO: number variable
        return 30;
    }

    void paintListBoxItem (int rowNumber, juce::Graphics& g,
                           int width, int height, bool rowIsSelected) override
    {
        //TODO: return members of a queue
        if (rowIsSelected)
            g.fillAll (juce::Colours::lightblue);

        g.setColour (juce::Colours::black);
        g.setFont (height * 0.7f);

        g.drawText ("Custom Item #" + juce::String (rowNumber + 1),
                    5, 0, width, height,
                    juce::Justification::centredLeft, true);
    }
/*
    juce::var getDragSourceDescription (const juce::SparseSet<int>& selectedRows) override
    {
        // for our drag description, we'll just make a comma-separated list of the selected row
        // numbers - this will be picked up by the drag target and displayed in its box.
        juce::StringArray rows;

        for (int i = 0; i < selectedRows.size(); ++i)
            rows.add (juce::String (selectedRows[i] + 1));

        return rows.joinIntoString (", ");
    }*/
};

class SongsListBox    : public juce::Component
{
public:
    SongsListBox();
    ~SongsListBox();

    void paint (juce::Graphics&) override;
    void resized() override;
    
    //TODO: insert, remove, getRowNumber functions

private:
    juce::ListBox sourceListBox;
    SongListBoxContents sourceModel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SongsListBox)
};


#endif  // SONGSLISTBOX_H_INCLUDED
