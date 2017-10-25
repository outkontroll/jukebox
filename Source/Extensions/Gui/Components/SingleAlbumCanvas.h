#ifndef SINGLEALBUMCANVAS_S
#define SINGLEALBUMCANVAS_S

#include "JuceHeader.h"

namespace jukebox { namespace gui {

class SingleAlbumCanvas : public juce::Component
{
public:
    SingleAlbumCanvas();
    void paint(juce::Graphics& g) override;

    void loadImage(const juce::String& imagePath);

private:
    juce::Rectangle<float> calculateImagePlace() const;

    juce::Image image;
};

}}

#endif // SINGLEALBUMCANVAS_S
