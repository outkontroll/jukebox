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

private:
    struct Position
    {
        int x;
        int y;
    };

    juce::Rectangle<float> calculateImagePlace(Position position, float slotWidth, float slotHeight) const;
    juce::Rectangle<float> calculateTextPlace(Position position, float slotWidth, float slotHeight) const;
    Position getPositionFromIndex(int index) const;

    std::vector<std::pair<juce::Image, int>> albums;
    int colums = 4;
    int rows = 2;
};

}}

#endif // MULTIIMAGECANVAS_H
