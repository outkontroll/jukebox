#ifndef MULTIPLEALBUMSCANVASPOSITIONCALCULATOR_H
#define MULTIPLEALBUMSCANVASPOSITIONCALCULATOR_H

#include "JuceHeader.h"

namespace jukebox::gui {

class MultipleAlbumsCanvasPositionCalculator
{
public:
    MultipleAlbumsCanvasPositionCalculator(float slotWidth, float slotHeight, int columns);

    juce::Rectangle<float> calculateImagePlace(int albumIndex) const;
    juce::Rectangle<float> calculateTextPlace(int albumIndex) const;
    juce::Rectangle<float> calculateSelectionPlace(const juce::Rectangle<float>& placeToSelect);
private:
    struct Position
    {
        const int x;
        const int y;
    };

    Position getPositionFromIndex(int index) const;

    const float slotWidth;
    const float slotHeight;
    const int columns;
    const float imageWidth;
};

}

#endif //MULTIPLEALBUMSCANVASPOSITIONCALCULATOR_H
