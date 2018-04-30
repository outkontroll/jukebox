#ifndef SINGLEALBUMPOSITIONCALCULATOR_H
#define SINGLEALBUMPOSITIONCALCULATOR_H

#include <vector>
#include <array>
#include "JuceHeader.h"

namespace jukebox::gui {

class SingleAlbumPositionCalculator
{
public:
    SingleAlbumPositionCalculator(float width, float height, float imageSize);

    juce::Rectangle<float> calculateImagePlace() const;
    juce::Rectangle<float> calculateAlbumTextPlace() const;
    juce::Rectangle<float> calculateArtistTextPlace() const;
    std::array<int, 3> calculateDrawableSongNamesPlace() const;
    std::vector<juce::Rectangle<float>> calculateSelectionBounds(const std::vector<juce::String>& lines, std::array<int, 3> position) const;

private:
    const float width;
    const float height;
    const float imageSize;
};

}

#endif //SINGLEALBUMPOSITIONCALCULATOR_H
