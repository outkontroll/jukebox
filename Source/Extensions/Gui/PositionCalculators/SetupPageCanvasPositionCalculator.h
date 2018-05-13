#ifndef SETUPPAGEPOSITIONCALCULATOR_H
#define SETUPPAGEPOSITIONCALCULATOR_H

#include "JuceHeader.h"

namespace jukebox::gui {

struct SetupPageCanvasPositionCalculator
{
    SetupPageCanvasPositionCalculator(int width, int height, float fontSize);

    juce::Rectangle<float> calculateTextPlace() const;
    juce::Rectangle<int> calculateInfoStatisticsBounds() const;
    juce::Rectangle<int> calculateTextStatisticsBounds() const;
    juce::Rectangle<int> calculateInfoTimeToPlayASong() const;
    juce::Rectangle<int> calculateComboTimeToPlayASong() const;
    juce::Rectangle<int> calculateInfoTimeToSaveInsertedCoins() const;
    juce::Rectangle<int> calculateComboTimeToSaveInsertedCoins() const;
    juce::Rectangle<int> calculateInfoTimeToPlayAdvertiseMusic() const;
    juce::Rectangle<int> calculateComboTimeToPlayAdvertiseMusic() const;
    juce::Rectangle<int> calculateChangePasswordBounds() const;
    juce::Rectangle<int> calculateNoPasswordToggleBounds() const;
    juce::Rectangle<int> calculatePasswordToggleBounds() const;

    const int width;
    const int height;
    const float fontSize;
    const int fontSizeInt;
    const int offsetX;
    const int offsetY;

    const int statisticsWidth;
    const int statisticsHeight;

    const int rightWidth;
};

}

#endif //SETUPPAGEPOSITIONCALCULATOR_H
