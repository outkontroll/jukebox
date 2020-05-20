#ifndef MULTIPLEALBUMSCANVASPOSITIONCALCULATOR_H
#define MULTIPLEALBUMSCANVASPOSITIONCALCULATOR_H

#include "JuceHeader.h"

namespace jukebox::gui {

class MultipleAlbumsPositionCalculator
{
public:
    MultipleAlbumsPositionCalculator(float slotWidth, float slotHeight, int columns);

    juce::Rectangle<float> calculateImagePlace(int albumIndex) const;
    //TODO testing
    juce::Rectangle<float> calculateTextPlace(int albumIndex) const;
    juce::Rectangle<float> calculateTextPlace2(int albumIndex) const;
    juce::Rectangle<float> calculateSelectionPlace(const juce::Rectangle<float>& placeToSelect);

    //TODO contour
    juce::Rectangle<float> calculateSlot(int albumIndex) const;
private:
    struct Position
    {
        const int x;
        const int y;
    };

    struct OuterOffsets
    {
        const float a;
        const float b;
        const float e;
        const float f;
    };

    struct InnerOffsets
    {
        const float p;
        const float x1;
        const float x2;
        const float t;
        const float y;
        const float z;
    };

    Position getPositionFromIndex(int index) const;
    OuterOffsets calculateOuterOffsets(float height, float width) const;
    InnerOffsets calculateInnerOffsets(OuterOffsets outerOffsets) const;

    const float slotWidth;
    const float slotHeight;
    const int columns;

    const OuterOffsets outerOffsets;
    const InnerOffsets innerOffsets;

    const float imageSize;
    const float textSize;
    const float selectionThickness;

};

}

#endif //MULTIPLEALBUMSCANVASPOSITIONCALCULATOR_H
