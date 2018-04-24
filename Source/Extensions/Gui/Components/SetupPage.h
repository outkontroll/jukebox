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
    virtual void setTimeToPlayASong(int millisecs);
    virtual void showStatistics(const std::string& statistics);

    jukebox::signals::Signal<const std::string&> musicDirectoryChangedSignal;
    jukebox::signals::Signal<int> timeToPlayASongChangedSignal;
private:
    juce::Rectangle<float> calculateTextPlace(float width, float height) const;

    juce::ScopedPointer<juce::Label> infoMusicDirectory;
    juce::ScopedPointer<juce::TextEditor> txtMusicDirectory;
    juce::ScopedPointer<juce::TextButton> buttonMusicDirectory;
    juce::ScopedPointer<juce::Label> infoStatistics;
    juce::ScopedPointer<juce::TextEditor> txtStatistics;
    juce::ScopedPointer<juce::Label> infoTimeToPlayASong;
    juce::ScopedPointer<juce::ComboBox> comboTimeToPlayASong;
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

    class TimeToPlayASongListener : public juce::ComboBox::Listener
    {
    public:
        TimeToPlayASongListener(SetupPage&);
        void comboBoxChanged(juce::ComboBox*) override;
    private:
        SetupPage& ownerPage;
    };
    juce::ScopedPointer<TimeToPlayASongListener> timeToPlayASongListener;
};

}

#endif //SETUPPAGE_H
