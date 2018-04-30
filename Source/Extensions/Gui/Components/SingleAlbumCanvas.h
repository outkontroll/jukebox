#ifndef SINGLEALBUMCANVAS_S
#define SINGLEALBUMCANVAS_S

#include "JuceHeader.h"
#include <string>
#include <memory>
#include <array>

namespace jukebox { namespace filesystem {
    class IFileSystem;
}}

namespace jukebox::gui {

class SingleAlbumCanvas : public juce::Component
{
public:
    void paint(juce::Graphics& g) override;
    void parentSizeChanged() override;

    void loadAlbum(const std::string& musicDirectory, unsigned int selectedAlbumIndex, const jukebox::filesystem::IFileSystem& fileSys);
    void setSelection(unsigned int selectedSongIndex);

private:
    void loadImage(const std::string& musicDirectory, const filesystem::IFileSystem& fileSys);
    auto loadInfoFile(const std::string& musicDirectory, const jukebox::filesystem::IFileSystem& fileSys, unsigned int albumIndex_) const
        -> std::tuple<juce::String, juce::String, std::vector<juce::String>>;

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
