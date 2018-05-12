#ifndef MUSICSETUPCANVASPOSITIONCALCULATOR_H
#define MUSICSETUPCANVASPOSITIONCALCULATOR_H

#include "JuceHeader.h"

namespace jukebox { namespace gui {

struct MusicSetupCanvasPositionCalculator
{
    MusicSetupCanvasPositionCalculator(int width, int height, float fontSize);

    juce::Rectangle<int> calculateInfoMusicDirectoryBounds() const;
    juce::Rectangle<int> calculateTextMusicDirectoryBounds() const;
    juce::Rectangle<int> calculateButtonMusicDirectoryBounds() const;
    juce::Rectangle<int> calculateTreeMusicDirectoryBounds() const;
    juce::Rectangle<int> calculateButtonImportBounds() const;
    juce::Rectangle<int> calculateImagePreviewBounds() const;

    const int width;
    const int height;
    const float fontSize;
    const int offsetX;
    const int offsetY;

    const int textWidth;
};

}}

#endif //MUSICSETUPCANVASPOSITIONCALCULATOR_H
