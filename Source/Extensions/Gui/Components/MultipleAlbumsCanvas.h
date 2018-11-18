#ifndef MULTIIMAGECANVAS_H
#define MULTIIMAGECANVAS_H

#include "JuceHeader.h"
#include <vector>
#include <string>

namespace jukebox { namespace audio {
    struct AlbumInfo;
}}

namespace jukebox { namespace gui {

class MultipleAlbumsCanvas : public juce::Component
{
public:
    void paint(juce::Graphics& g) override;
    void parentSizeChanged() override;

    void loadAlbums(const std::vector<jukebox::audio::AlbumInfo>& visibleAlbums, int firstAlbumIndex);
    void setSelection(int selectedAlbumIndex);
    void changeLayout(int rows, int columns);

private:
    struct AlbumPositionInfo
    {
        const juce::Rectangle<float> imagePlace;
        const juce::Rectangle<float> textPlace;
    };

    struct VisibleAlbum
    {
        const juce::Image image;
        const AlbumPositionInfo position;
        const int albumNumber;
    };

    std::vector<AlbumPositionInfo> albumPositions;
    std::vector<VisibleAlbum> visibleAlbums;
    std::vector<AlbumPositionInfo> selectionPlaces;
    juce::Rectangle<float> selectionImagePlace;
    juce::Rectangle<float> selectionTextPlace;
    int columns = 4;
    int rows = 2;
    int selectedAlbumIndex = 1;
    float slotWidth = 0;
    float slotHeight = 0;
};

}}

#endif // MULTIIMAGECANVAS_H
