#ifndef SETUPPAGE_H
#define SETUPPAGE_H

#include "JuceHeader.h"

namespace jukebox::gui {

class SetupPage : public juce::Component
{
public:
    void paint(juce::Graphics& g) override;
    void parentSizeChanged() override;

private:
    juce::Rectangle<float> calculateTextPlace(float width, float height) const;

    juce::Rectangle<float> textPlace = {0, 0, 0, 0};
};

}

#endif //SETUPPAGE_H
