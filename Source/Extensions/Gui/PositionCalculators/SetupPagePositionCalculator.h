#ifndef SETUPPAGEPOSITIONCALCULATOR_H
#define SETUPPAGEPOSITIONCALCULATOR_H

#include "JuceHeader.h"

namespace jukebox::gui {

struct SetupPagePositionCalculator
{
    juce::Rectangle<float> calculateTextPlace() const;
    juce::Rectangle<int> calculateChangePasswordBounds() const;

    const int width;
    const int height;
    const float fontSize;
};

}

#endif //SETUPPAGEPOSITIONCALCULATOR_H
