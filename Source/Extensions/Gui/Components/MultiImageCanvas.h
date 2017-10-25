#ifndef MULTIIMAGECANVAS_H
#define MULTIIMAGECANVAS_H

#include "JuceHeader.h"
#include <vector>

namespace jukebox { namespace gui {

class MultiImageCanvas : public juce::Component
{
public:
    MultiImageCanvas();
    void paint(juce::Graphics& g) override;

    void loadImage(const juce::String& imagePath);

private:
    struct Position
    {
        float x;
        float y;
    };

    juce::Rectangle<float> calculateImagePlace(Position position) const;

    std::vector<juce::Image> images;
};

}}

#endif // MULTIIMAGECANVAS_H
