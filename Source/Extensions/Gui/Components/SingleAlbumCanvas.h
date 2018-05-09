#ifndef SINGLEALBUMCANVAS_S
#define SINGLEALBUMCANVAS_S

#include "JuceHeader.h"
#include <string>
#include <memory>
#include <array>

namespace jukebox { namespace audio {
    struct AlbumInfo;
}}

namespace jukebox::gui {

class SingleAlbumCanvas : public juce::Component
{
public:
    void paint(juce::Graphics& g) override;
    void parentSizeChanged() override;

    void loadAlbum(const std::vector<jukebox::audio::AlbumInfo>& albums, unsigned int selectedAlbumIndex);
    void setSelection(unsigned int selectedSongIndex);

private:
    juce::Image image;
    juce::String artistName = "";
    juce::String drawableSongNames = "";
    std::vector<juce::String> songNames;
    unsigned int albumIndex = 0;
    juce::Rectangle<float> albumTextPlace = {0, 0, 0, 0};
    juce::Rectangle<float> imagePlace = {0, 0, 0, 0};
    juce::Rectangle<float> artistNamePlace = {0, 0, 0, 0};
    std::vector<juce::Rectangle<float>> selectionBounds;
    std::array<int, 3> drawableSongNamesPlace = {0, 0, 0};
    unsigned int currentSelectedLine = 0;
};

}

#endif // SINGLEALBUMCANVAS_S
