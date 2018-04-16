#ifndef SETUPPAGE_H
#define SETUPPAGE_H

#include "JuceHeader.h"
#include "Signals.hpp"

namespace jukebox::gui {

class SetupPage : public juce::Component
{
public:
    SetupPage();
    ~SetupPage() override;

    void paint(juce::Graphics& g) override;
    void parentSizeChanged() override;

    virtual void setMusicDirectory(const std::string& musicDirectory);
    virtual void showStatistics(const std::string& statistics);

    jukebox::signals::Signal<const std::string&> musicDirectoryChangedSignal;
private:
    juce::Rectangle<float> calculateTextPlace(float width, float height) const;

    juce::ScopedPointer<juce::Label> infoMusicDirectory;
    juce::ScopedPointer<juce::TextEditor> txtMusicDirectory;
    juce::ScopedPointer<juce::TextButton> buttonMusicDirectory;
    juce::ScopedPointer<juce::Label> infoStatistics;
    juce::ScopedPointer<juce::TextEditor> txtStatistics;
    juce::Rectangle<float> textPlace = {0, 0, 0, 0};

    class MusicDirectoryListener : public juce::Button::Listener
    {
    public:
        MusicDirectoryListener(SetupPage& owner);
        void buttonClicked(juce::Button*) override;
    private:
        SetupPage& ownerPage;
    };
    juce::ScopedPointer<MusicDirectoryListener> musicDirectoryListener;
};

}

#endif //SETUPPAGE_H
