#ifndef SETUPPAGE_H
#define SETUPPAGE_H

#include "JuceHeader.h"
#include "Signals.hpp"

namespace jukebox {
    class Password;
}

namespace jukebox::gui {

class SetupPage : public juce::Component,
                  public juce::TextButton::Listener,
                  public juce::ComboBox::Listener
{
public:
    SetupPage();
    ~SetupPage() override;

    void paint(juce::Graphics& g) override;
    void parentSizeChanged() override;
    void buttonClicked(juce::Button*) override;
    void comboBoxChanged(juce::ComboBox*) override;

    virtual void setTimeToPlayASong(int millisecs);
    virtual void setTimeToSaveInsertedCoins(int millisecs);
    virtual void showStatistics(const std::string& statistics);
    virtual void setPassword(const jukebox::Password* password);
    virtual void turnOffPassword();

    jukebox::signals::Signal<int> timeToPlayASongChangedSignal;
    jukebox::signals::Signal<int> timeToSaveInsertedCoinsChangedSignal;
    jukebox::signals::Signal<const jukebox::Password&> passwordChangedSignal;
    jukebox::signals::Signal<> passwordTurnedOffSignal;

private:
    void showChangePasswordDialog();
    void showWrongPasswordDialog();
    void showDifferentPasswordsDialog();

    juce::ScopedPointer<juce::Label> infoStatistics;
    juce::ScopedPointer<juce::TextEditor> txtStatistics;
    juce::ScopedPointer<juce::Label> infoTimeToPlayASong;
    juce::ScopedPointer<juce::ComboBox> comboTimeToPlayASong;
    juce::ScopedPointer<juce::Label> infoTimeToSaveInsertedCoins;
    juce::ScopedPointer<juce::ComboBox> comboTimeToSaveInsertedCoins;
    juce::ScopedPointer<juce::TextButton> buttonChangePassword;

    juce::Rectangle<float> textPlace = {0, 0, 0, 0};

    const jukebox::Password* password = nullptr;
};

}

#endif //SETUPPAGE_H
