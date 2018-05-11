#ifndef MUSICSETUPCANVAS_H
#define MUSICSETUPCANVAS_H

#include "JuceHeader.h"
#include "Signals.hpp"

namespace jukebox::gui {

class MusicDirectoryListener;

class MusicSetupCanvas : public juce::Component, public juce::FileBrowserListener
{
public:
    MusicSetupCanvas();
    ~MusicSetupCanvas() override;

    void paint(juce::Graphics& g) override;
    void parentSizeChanged() override;

    virtual void setMusicDirectory(const std::string& musicDirectory);

    jukebox::signals::Signal<const std::string&> musicDirectoryChangedSignal;
    jukebox::signals::Signal<> lostFocusSignal;

private:
    void selectionChanged() override;
    void fileClicked (const juce::File&, const juce::MouseEvent&) override {}
    void fileDoubleClicked (const juce::File&) override {}
    void browserRootChanged (const juce::File&) override {}
    bool isImageFile(const juce::File&) const;

    juce::ScopedPointer<juce::Label> infoMusicDirectory;
    juce::ScopedPointer<juce::TextEditor> txtMusicDirectory;
    juce::ScopedPointer<juce::TextButton> buttonMusicDirectory;

    juce::ScopedPointer<juce::FileTreeComponent> treeMusicDir;
    juce::TimeSliceThread directoryThread{ "Music File Scanner Thread" };
    juce::DirectoryContentsList listToShow{nullptr, directoryThread};
    juce::ImageComponent imagePreview;
    juce::Rectangle<float> textPlace = {0, 0, 0, 0};

    juce::ScopedPointer<MusicDirectoryListener> musicDirectoryListener;

    friend class MusicDirectoryListener;
};

}

#endif //MUSICSETUPCANVAS_H
