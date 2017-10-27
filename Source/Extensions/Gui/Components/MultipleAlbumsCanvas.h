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

    void loadAlbums(const std::string& musicDirectoy, int firstAlbumIndex);
    void setSelection(int selectedAlbumIndex);

private:
    struct Position
    {
        int x;
        int y;
    };

    juce::Rectangle<float> calculateImagePlace(Position position, float slotWidth, float slotHeight) const;
    juce::Rectangle<float> calculateTextPlace(Position position, float slotWidth, float slotHeight) const;
    juce::Rectangle<float> calculateSelectionPlace(const juce::Rectangle<float>& placeToSelect);
    Position getPositionFromIndex(int index) const;

    std::vector<std::pair<juce::Image, int>> albums;
    int colums = 4;
    int rows = 2;
    int selectedAlbumIndex = 1;
};

}}

#endif // MULTIIMAGECANVAS_H
