#ifndef SINGLEALBUMCANVAS_S
#define SINGLEALBUMCANVAS_S

#include "JuceHeader.h"
#include <string>

namespace jukebox { namespace gui {

class SingleAlbumCanvas : public juce::Component
{
public:
    void paint(juce::Graphics& g) override;

    void loadAlbum(const std::string& musicDirectory, int firstAlbumIndex);

private:
    juce::Rectangle<float> calculateImagePlace(float imageSize) const;
    juce::Rectangle<float> calculateTextPlace(float imageSize) const;

    juce::Image image;
    int albumIndex;
};

}}

#endif // SINGLEALBUMCANVAS_S
