#ifndef SETUPPAGEPOSITIONCALCULATOR_H
#define SETUPPAGEPOSITIONCALCULATOR_H

#include "JuceHeader.h"

namespace jukebox::gui {

struct SetupPagePositionCalculator
{
    juce::Rectangle<float> calculateTextPlace(float width, float height, float fontSize) const;
};

}

#endif //SETUPPAGEPOSITIONCALCULATOR_H
