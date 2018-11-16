#ifndef MUSICSETUPCANVASPOSITIONCALCULATOR_H
#define MUSICSETUPCANVASPOSITIONCALCULATOR_H

#include "JuceHeader.h"

namespace jukebox { namespace gui {

struct MusicSetupCanvasPositionCalculator
{
    MusicSetupCanvasPositionCalculator(int width, int height, float fontSize, int columns);

    juce::Rectangle<int> calculateInfoMusicDirectoryBounds() const;
    juce::Rectangle<int> calculateTextMusicDirectoryBounds() const;
    juce::Rectangle<int> calculateButtonMusicDirectoryBounds() const;
    juce::Rectangle<int> calculateTreeMusicDirectoryBounds() const;
    juce::Rectangle<int> calculateButtonImportBounds() const;
    juce::Rectangle<int> calculateImagePreviewBounds() const;
    juce::Rectangle<int> calculateInfoArtistBounds() const;
    juce::Rectangle<int> calculateTextArtistBounds() const;
    juce::Rectangle<int> calculateInfoTitleBounds() const;
    juce::Rectangle<int> calculateTextTitleBounds() const;
    juce::Rectangle<int> calculateInfoSongsBounds() const;
    juce::Rectangle<int> calculateTextSongsBounds() const;

    const int width;
    const int height;
    const float fontSize;
    const int columns;
    const int fontSizeInt;
    const int offsetX;
    const int offsetY;

    const int musicTextWidth;
    const int imageWidth;
    const int imageHeight;
    const int imageBottom;
    const int rightSideLeft;
    const int rightSideTextWidth;
};

}}

#endif //MUSICSETUPCANVASPOSITIONCALCULATOR_H
