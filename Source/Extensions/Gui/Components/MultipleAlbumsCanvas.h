#ifndef MULTIIMAGECANVAS_H
#define MULTIIMAGECANVAS_H

#include "JuceHeader.h"
#include <vector>
#include <string>

namespace jukebox { namespace gui {

class MultipleAlbumsCanvas : public juce::Component
{
public:
    void paint(juce::Graphics& g) override;
    void parentSizeChanged() override;

    void loadAlbums(const std::string& musicDirectoy, int firstAlbumIndex);
    void setSelection(int selectedAlbumIndex);

private:
    struct Position
    {
        const int x;
        const int y;
    };

    juce::Rectangle<float> calculateImagePlace(Position position, float slotWidth, float slotHeight) const;
    juce::Rectangle<float> calculateTextPlace(Position position, float slotWidth, float slotHeight) const;
    juce::Rectangle<float> calculateSelectionPlace(const juce::Rectangle<float>& placeToSelect);
    Position getPositionFromIndex(int index) const;

    struct VisibleAlbum
    {
        const juce::Image image;
        const int albumNumber;
        const juce::Rectangle<float> imagePlace;
        const juce::Rectangle<float> textPlace;
    };

    std::vector<VisibleAlbum> albums;
    juce::Rectangle<float> selectionImagePlace;
    juce::Rectangle<float> selectionTextPlace;
    int colums = 4;
    int rows = 2;
    int selectedAlbumIndex = 1;
    float slotWidth = 0;
    float slotHeight = 0;
};

}}

#endif // MULTIIMAGECANVAS_H
