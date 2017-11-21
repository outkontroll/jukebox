#ifndef SINGLEALBUMCANVAS_S
#define SINGLEALBUMCANVAS_S

#include "JuceHeader.h"
#include <string>
#include <memory>

namespace jukebox { namespace gui {

class SelectableMultiLineText;

class SingleAlbumCanvas : public juce::Component
{
public:
    void paint(juce::Graphics& g) override;
    void parentSizeChanged() override;

    void loadAlbum(const std::string& musicDirectory, int selectedAlbumIndex);

private:
    struct MultipleLinesPosition
    {
        int startX;
        int baselineY;
        int maximumLineWidth;
    };

    void drawMultiLines(const juce::String& text, const std::vector<juce::String>& lines, MultipleLinesPosition position, juce::Graphics& g);

    void loadImage(const std::string& musicDirectory);
    void loadInfoFile(const std::string& musicDirectory);

    juce::Rectangle<float> calculateImagePlace(float imageSize, float width, float height) const;
    juce::Rectangle<float> calculateTextPlace(float imageSize, float width) const;
    juce::Rectangle<float> calculateArtistTextPlace(float imageSize, float width) const;
    MultipleLinesPosition calculateOtherLinesPlace(float imageSize, float width, float height) const;

    juce::Image image;
    juce::String artistName = "";
    juce::String otherLines;
    std::vector<juce::String> allTheOtherLines;
    int albumIndex;
    juce::Rectangle<float> textPlace;
    juce::Rectangle<float> imagePlace;
    juce::Rectangle<float> artistNamePlace;
    MultipleLinesPosition otherLinesPlace;
    int currentSelectedLine = 0;
};

}}

#endif // SINGLEALBUMCANVAS_S
