#ifndef MUSICSETUPCANVAS_H
#define MUSICSETUPCANVAS_H

#include "JuceHeader.h"
#include "Signals.hpp"

namespace jukebox::audio {
    struct AlbumInfo;
}

namespace jukebox::gui {

class MusicDirectoryListener;

class MusicSetupCanvas : public juce::Component,
                         public juce::Button::Listener,
                         public juce::FileBrowserListener
{
public:
    MusicSetupCanvas();
    ~MusicSetupCanvas() override;

    void paint(juce::Graphics& g) override;
    void parentSizeChanged() override;

    virtual void setMusicDirectory(const std::string& musicDirectory);
    virtual void setAlbumsForMusicSetup(const std::vector<jukebox::audio::AlbumInfo>& albums);

    jukebox::signals::Signal<const std::string&> musicDirectoryChangedSignal;
    jukebox::signals::Signal<> lostFocusSignal;

private:
    void buttonClicked(juce::Button*) override;

    void selectionChanged() override;
    void fileClicked (const juce::File&, const juce::MouseEvent&) override {}
    void fileDoubleClicked (const juce::File&) override {}
    void browserRootChanged (const juce::File&) override {}

    void selectMusicDirectory();
    void importMusicDirectory();
    void loadImage(const audio::AlbumInfo& albumInfo);
    void loadTextFile(const audio::AlbumInfo& albumInfo);

    juce::ScopedPointer<juce::Label> infoMusicDirectory;
    juce::ScopedPointer<juce::TextEditor> txtMusicDirectory;
    juce::ScopedPointer<juce::TextButton> buttonMusicDirectory;
    juce::ScopedPointer<juce::TextButton> buttonImport;
    juce::ScopedPointer<juce::Label> infoArtist;
    juce::ScopedPointer<juce::TextEditor> txtArtist;
    juce::ScopedPointer<juce::Label> infoTitle;
    juce::ScopedPointer<juce::TextEditor> txtTitle;
    juce::ScopedPointer<juce::Label> infoSongNames;
    juce::ScopedPointer<juce::TextEditor> txtSongNames;

    juce::ScopedPointer<juce::FileTreeComponent> treeMusicDir;
    juce::TimeSliceThread directoryThread{ "Music File Scanner Thread" };
    juce::DirectoryContentsList listToShow{nullptr, directoryThread};
    juce::ImageComponent imagePreview;
    juce::File currentVisibleDirectory;
    const std::vector<jukebox::audio::AlbumInfo>* albums = nullptr;
};

}

#endif //MUSICSETUPCANVAS_H
