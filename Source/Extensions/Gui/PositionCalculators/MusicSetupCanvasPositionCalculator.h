#ifndef MUSICSETUPCANVASPOSITIONCALCULATOR_H
#define MUSICSETUPCANVASPOSITIONCALCULATOR_H

#include "JuceHeader.h"

namespace jukebox { namespace gui {

struct MusicSetupCanvasPositionCalculator
{
    juce::Rectangle<float> calculateTextPlace(float width, float height, float fontSize) const;
};

}}

#endif //MUSICSETUPCANVASPOSITIONCALCULATOR_H
