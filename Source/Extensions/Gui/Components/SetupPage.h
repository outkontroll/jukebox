#ifndef SETUPPAGE_H
#define SETUPPAGE_H

#include "JuceHeader.h"
#include "Signals.hpp"

namespace jukebox::gui {
class TimeToPlayASongListener;
class TimeToSaveInsertedCoinsListener;

class SetupPage : public juce::Component
{
public:
    SetupPage();
    ~SetupPage() override;

    void paint(juce::Graphics& g) override;
    void parentSizeChanged() override;

    virtual void setTimeToPlayASong(int millisecs);
    virtual void setTimeToSaveInsertedCoins(int millisecs);
    virtual void showStatistics(const std::string& statistics);

    jukebox::signals::Signal<int> timeToPlayASongChangedSignal;
    jukebox::signals::Signal<int> timeToSaveInsertedCoinsChangedSignal;

private:
    juce::ScopedPointer<juce::Label> infoStatistics;
    juce::ScopedPointer<juce::TextEditor> txtStatistics;
    juce::ScopedPointer<juce::Label> infoTimeToPlayASong;
    juce::ScopedPointer<juce::ComboBox> comboTimeToPlayASong;
    juce::ScopedPointer<juce::Label> infoTimeToSaveInsertedCoins;
    juce::ScopedPointer<juce::ComboBox> comboTimeToSaveInsertedCoins;

    juce::Rectangle<float> textPlace = {0, 0, 0, 0};

    juce::ScopedPointer<TimeToPlayASongListener> timeToPlayASongListener;
    juce::ScopedPointer<TimeToSaveInsertedCoinsListener> timeToSaveInsertedCoinsListener;

    friend class TimeToPlayASongListener;
    friend class TimeToSaveInsertedCoinsListener;
};

}

#endif //SETUPPAGE_H
