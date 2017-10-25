#ifndef MULTIIMAGECANVAS_H
#define MULTIIMAGECANVAS_H

#include "JuceHeader.h"
#include <vector>

namespace jukebox { namespace gui {

class MultipleAlbumsCanvas : public juce::Component
{
public:
    MultipleAlbumsCanvas();
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
