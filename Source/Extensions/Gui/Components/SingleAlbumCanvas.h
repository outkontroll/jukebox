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

    void loadAlbum(const std::string& musicDirectory, unsigned int selectedAlbumIndex);
    void setSelection(unsigned int selectedSongIndex);

private:
    struct MultipleLinesPosition
    {
        int startX;
        int baselineY;
        int maximumLineWidth;
    };

    void loadImage(const std::string& musicDirectory);
    void loadInfoFile(const std::string& musicDirectory);

    juce::Rectangle<float> calculateImagePlace(float imageSize, float width, float height) const;
    juce::Rectangle<float> calculateTextPlace(float imageSize, float width) const;
    juce::Rectangle<float> calculateArtistTextPlace(float imageSize, float width) const;
    juce::Rectangle<float> calculateSelectionBounds(const std::vector<juce::String>& lines, MultipleLinesPosition position);
    MultipleLinesPosition calculateOtherLinesPlace(float imageSize, float width, float height) const;

    juce::Image image;
    juce::String artistName = "";
    juce::String otherLines = "";
    std::vector<juce::String> songNames;
    unsigned int albumIndex = 0;
    juce::Rectangle<float> textPlace = {0, 0, 0, 0};
    juce::Rectangle<float> imagePlace = {0, 0, 0, 0};
    juce::Rectangle<float> artistNamePlace = {0, 0, 0, 0};
    juce::Rectangle<float> selectionBounds = {0, 0, 0, 0};
    MultipleLinesPosition otherLinesPlace;
    unsigned int currentSelectedLine = 0;
};

}}

#endif // SINGLEALBUMCANVAS_S
