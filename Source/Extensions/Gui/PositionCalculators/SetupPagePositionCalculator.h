#ifndef SETUPPAGEPOSITIONCALCULATOR_H
#define SETUPPAGEPOSITIONCALCULATOR_H

#include "JuceHeader.h"

namespace jukebox::gui {

struct SetupPagePositionCalculator
{
    SetupPagePositionCalculator(int width, int height, float fontSize);

    juce::Rectangle<float> calculateTextPlace() const;
    juce::Rectangle<int> calculateChangePasswordBounds() const;
    juce::Rectangle<int> calculateStatisticsBounds() const;
    juce::Rectangle<int> calculateNoPasswordToggleBounds() const;
    juce::Rectangle<int> calculatePasswordToggleBounds() const;

    const int width;
    const int height;
    const float fontSize;
    const int offsetX;
    const int offsetY;

    const int statisticsWidth;
    const int statisticsHeight;

    const int rightWidth;
};

}

#endif //SETUPPAGEPOSITIONCALCULATOR_H
