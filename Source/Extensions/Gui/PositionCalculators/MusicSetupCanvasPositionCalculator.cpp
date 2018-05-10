#include "MusicSetupCanvasPositionCalculator.h"

using namespace jukebox::gui;
using namespace juce;

juce::Rectangle<float> MusicSetupCanvasPositionCalculator::calculateTextPlace(float width, float height, float fontSize) const
{
    const float xPosition = width / 2;
    const float yPosition = height / 3;
    const float textHeight = fontSize;
    const float textWidth = width;

    return { xPosition, yPosition, textWidth, textHeight };
}
