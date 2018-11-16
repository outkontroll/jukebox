#include "SetupPageCanvas.h"
#include "SetupPageCanvasPositionCalculator.h"
#include "Password.h"

using namespace jukebox::gui;
using namespace juce;

namespace {
    const float bigFontSize = 24.0f;
    const float smallFontSize = 18.0f;
    const char* setupPageName = "Setup";
}

int getSelectedIndexFromSaveInsertedCoinHours(int SaveInsertedCoinHours);
int getSaveInsertedCoinHoursFromSelected(int selectedIndex);
int getTimeToPlayAdvertiseMusicFromSelected(int selectedIndex);
int getSelectedIndexFromPlayAdvertiseMusic(int timeToPlayAdvertiseMusic);

SetupPageCanvas::SetupPageCanvas()
{
    addAndMakeVisible(infoStatistics = new Label("statistics info label", "Statistics:"));
    infoStatistics->setFont (Font (smallFontSize, Font::plain));
    infoStatistics->setJustificationType (Justification::centredLeft);
    infoStatistics->setEditable (false, false, false);
    infoStatistics->setColour (TextEditor::textColourId, Colours::black);
    infoStatistics->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible(infoInsertedAll = new Label("all time inserted coins label", "Inserted:"));
    infoInsertedAll->setFont (Font (smallFontSize, Font::plain));
    infoInsertedAll->setJustificationType (Justification::centredLeft);
    infoInsertedAll->setEditable (false, false, false);
    infoInsertedAll->setColour (TextEditor::textColourId, Colours::black);
    infoInsertedAll->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible(txtInsertedAll = new TextEditor("all time inserted coins text"));
    txtInsertedAll->setReadOnly(true);
    txtInsertedAll->setScrollbarsShown(false);
    txtInsertedAll->setCaretVisible(false);
    txtInsertedAll->setPopupMenuEnabled(true);
    txtInsertedAll->setText(String());

    addAndMakeVisible(infoInsertedSinceLastSave = new Label("inserted coins since last save label", "Inserted since last save:"));
    infoInsertedSinceLastSave->setFont (Font (smallFontSize, Font::plain));
    infoInsertedSinceLastSave->setJustificationType (Justification::centredLeft);
    infoInsertedSinceLastSave->setEditable (false, false, false);
    infoInsertedSinceLastSave->setColour (TextEditor::textColourId, Colours::black);
    infoInsertedSinceLastSave->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible(txtInsertedSinceLastSave = new TextEditor("all time inserted coins text"));
    txtInsertedSinceLastSave->setReadOnly(true);
    txtInsertedSinceLastSave->setScrollbarsShown(false);
    txtInsertedSinceLastSave->setCaretVisible(false);
    txtInsertedSinceLastSave->setPopupMenuEnabled(true);
    txtInsertedSinceLastSave->setText(String());

    addAndMakeVisible(txtStatistics = new TextEditor("statistics text"));
    txtStatistics->setMultiLine(true);
    txtStatistics->setReturnKeyStartsNewLine(false);
    txtStatistics->setReadOnly(true);
    txtStatistics->setScrollbarsShown(true);
    txtStatistics->setCaretVisible(false);
    txtStatistics->setPopupMenuEnabled(true);
    txtStatistics->setText(String());

    addAndMakeVisible(infoTimeToPlayASong = new Label("time to play a song label", "Seconds to cancel playing a song"));
    infoTimeToPlayASong->setFont (Font (smallFontSize, Font::plain));
    infoTimeToPlayASong->setJustificationType (Justification::centredLeft);
    infoTimeToPlayASong->setEditable (false, false, false);
    infoTimeToPlayASong->setColour (TextEditor::textColourId, Colours::black);
    infoTimeToPlayASong->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible(comboTimeToPlayASong = new ComboBox("time to play a song combo"));
    comboTimeToPlayASong->addItem("0", 1);
    comboTimeToPlayASong->addItem("1", 2);
    comboTimeToPlayASong->addItem("2", 3);
    comboTimeToPlayASong->addItem("3", 4);
    comboTimeToPlayASong->addItem("4", 5);
    comboTimeToPlayASong->addItem("5", 6);
    comboTimeToPlayASong->addListener(this);

    addAndMakeVisible(infoTimeToSaveInsertedCoins = new Label("interval hours to save inserted coins label", "Hours between savings of inserted coins"));
    infoTimeToSaveInsertedCoins->setFont (Font (smallFontSize, Font::plain));
    infoTimeToSaveInsertedCoins->setJustificationType (Justification::centredLeft);
    infoTimeToSaveInsertedCoins->setEditable (false, false, false);
    infoTimeToSaveInsertedCoins->setColour (TextEditor::textColourId, Colours::black);
    infoTimeToSaveInsertedCoins->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible(comboTimeToSaveInsertedCoins = new ComboBox("interval hours to save inserted coins"));
    comboTimeToSaveInsertedCoins->addItem("1", 1);
    comboTimeToSaveInsertedCoins->addItem("6", 2);
    comboTimeToSaveInsertedCoins->addItem("12", 3);
    comboTimeToSaveInsertedCoins->addItem("24", 4);
    comboTimeToSaveInsertedCoins->addListener(this);

    addAndMakeVisible(infoTimeToPlayAdvertiseMusic = new Label("time to play advertise music label", "Minutes to play advertise music"));
    infoTimeToPlayAdvertiseMusic->setFont (Font (smallFontSize, Font::plain));
    infoTimeToPlayAdvertiseMusic->setJustificationType (Justification::centredLeft);
    infoTimeToPlayAdvertiseMusic->setEditable (false, false, false);
    infoTimeToPlayAdvertiseMusic->setColour (TextEditor::textColourId, Colours::black);
    infoTimeToPlayAdvertiseMusic->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible(comboTimeToPlayAdvertiseMusic = new ComboBox("time to play advertise music combo"));
    comboTimeToPlayAdvertiseMusic->addItem("Off", 1);
    comboTimeToPlayAdvertiseMusic->addItem("5", 2);
    comboTimeToPlayAdvertiseMusic->addItem("10", 3);
    comboTimeToPlayAdvertiseMusic->addItem("20", 4);
    comboTimeToPlayAdvertiseMusic->addItem("30", 5);
    comboTimeToPlayAdvertiseMusic->addItem("60", 6);
    comboTimeToPlayAdvertiseMusic->addListener(this);

    addAndMakeVisible(buttonChangePassword = new TextButton("change password button"));
    buttonChangePassword->setButtonText("Change password");
    buttonChangePassword->addListener(this);

    addAndMakeVisible(toggleNoPassword = new ToggleButton("No password"));
    toggleNoPassword->setRadioGroupId(12);
    toggleNoPassword->addListener(this);

    addAndMakeVisible(togglePassword = new ToggleButton("Password set"));
    togglePassword->setRadioGroupId(12);
    togglePassword->addListener(this);
}

SetupPageCanvas::~SetupPageCanvas()
{
    comboTimeToPlayASong->removeListener(this);
    comboTimeToSaveInsertedCoins->removeListener(this);
    comboTimeToPlayAdvertiseMusic->removeListener(this);
    buttonChangePassword->removeListener(this);
    toggleNoPassword->removeListener(this);
    togglePassword->removeListener(this);

    infoStatistics = nullptr;
    txtStatistics = nullptr;
    infoTimeToPlayASong = nullptr;
    comboTimeToPlayASong = nullptr;
    infoTimeToSaveInsertedCoins = nullptr;
    comboTimeToSaveInsertedCoins = nullptr;
    infoTimeToPlayAdvertiseMusic = nullptr;
    comboTimeToPlayAdvertiseMusic = nullptr;
    buttonChangePassword = nullptr;
    toggleNoPassword = nullptr;
    togglePassword = nullptr;
}

void SetupPageCanvas::paint(Graphics& g)
{
    g.setColour(Colours::black);
    g.drawRect(Rectangle<int>{0, 0, getWidth(), getHeight()});

    g.setFont(bigFontSize);

    // album's number
    g.drawText(setupPageName, textPlace, Justification::centredLeft);
}

void SetupPageCanvas::parentSizeChanged()
{
    SetupPageCanvasPositionCalculator calc{getWidth(), getHeight(), bigFontSize};

    textPlace = calc.calculateTextPlace();
    infoInsertedAll->setBounds(calc.calculateInfoInsertedAllBounds());
    txtInsertedAll->setBounds(calc.calculateTextInsertedAllBounds());
    infoInsertedSinceLastSave->setBounds(calc.calculateInfoInsertedSinceLastSaveBounds());
    txtInsertedSinceLastSave->setBounds(calc.calculateTextInsertedSinceLastSaveBounds());
    infoStatistics->setBounds(calc.calculateInfoStatisticsBounds());
    txtStatistics->setBounds(calc.calculateTextStatisticsBounds());
    txtStatistics->setFont(bigFontSize);
    infoTimeToPlayASong->setBounds(calc.calculateInfoTimeToPlayASong());
    comboTimeToPlayASong->setBounds(calc.calculateComboTimeToPlayASong());
    infoTimeToSaveInsertedCoins->setBounds(calc.calculateInfoTimeToSaveInsertedCoins());
    comboTimeToSaveInsertedCoins->setBounds(calc.calculateComboTimeToSaveInsertedCoins());
    infoTimeToPlayAdvertiseMusic->setBounds(calc.calculateInfoTimeToPlayAdvertiseMusic());
    comboTimeToPlayAdvertiseMusic->setBounds(calc.calculateComboTimeToPlayAdvertiseMusic());
    buttonChangePassword->setBounds(calc.calculateChangePasswordBounds());
    toggleNoPassword->setBounds(calc.calculateNoPasswordToggleBounds());
    togglePassword->setBounds(calc.calculatePasswordToggleBounds());
}

void SetupPageCanvas::buttonClicked(Button* button)
{
    if(button == buttonChangePassword)
    {
        showChangePasswordDialog();
    }
    else if(button == toggleNoPassword)
    {
        if(toggleNoPassword->getToggleState())
            handleNoPasswordToggle();
    }
    else if(button == togglePassword)
    {
        if(togglePassword->getToggleState())
            handlePasswordToggle();
    }
}

int getSelectedIndexFromSaveInsertedCoinHours(int SaveInsertedCoinHours)
{
    switch(SaveInsertedCoinHours)
    {
    case 1: return 1;
    case 6: return 2;
    case 12: return 3;
    case 24: return 4;
    }

    return 4;
}

int getSelectedIndexFromPlayAdvertiseMusic(int timeToPlayAdvertiseMusic)
{
    switch(timeToPlayAdvertiseMusic)
    {
    case 0: return 1;
    case 5: return 2;
    case 10: return 3;
    case 20: return 4;
    case 30: return 5;
    case 60: return 6;
    }

    return 4;
}

int getSaveInsertedCoinHoursFromSelected(int selectedIndex)
{
    switch(selectedIndex)
    {
    case 1: return 1;
    case 2: return 6;
    case 3: return 12;
    case 4: return 24;
    }

    return 24;
}

int getTimeToPlayAdvertiseMusicFromSelected(int selectedIndex)
{
    switch(selectedIndex)
    {
    case 1: return 0;
    case 2: return 5;
    case 3: return 10;
    case 4: return 20;
    case 5: return 30;
    case 6: return 60;
    }

    return 20;
}

void SetupPageCanvas::comboBoxChanged(ComboBox* combo)
{
    if(combo == comboTimeToPlayASong)
    {
        timeToPlayASongChangedSignal((combo->getSelectedId() - 1) * 1000);
    }
    else if(combo == comboTimeToSaveInsertedCoins)
    {
        timeToSaveInsertedCoinsChangedSignal(getSaveInsertedCoinHoursFromSelected(combo->getSelectedId()) * 3600 * 1000);
    }
    else if(combo == comboTimeToPlayAdvertiseMusic)
    {
        timeToPlayAdvertiseMusicChangedSignal(getTimeToPlayAdvertiseMusicFromSelected(combo->getSelectedId()) * 60 * 1000);
    }
}

void SetupPageCanvas::setTimeToPlayASong(int millisecs)
{
    comboTimeToPlayASong->setSelectedId(millisecs / 1000 + 1, dontSendNotification);
}

void SetupPageCanvas::setTimeToSaveInsertedCoins(int millisecs)
{
    comboTimeToSaveInsertedCoins->setSelectedId(getSelectedIndexFromSaveInsertedCoinHours(millisecs / (1000 * 3600)), dontSendNotification);
}

void SetupPageCanvas::setTimeToPlayAdvertiseMusic(int millisecs)
{
    comboTimeToPlayAdvertiseMusic->setSelectedId(getSelectedIndexFromPlayAdvertiseMusic(millisecs / (1000 * 60)), dontSendNotification);
}

void SetupPageCanvas::showStatistics(const std::string& statistics)
{
    txtStatistics->setText(statistics);
}

void SetupPageCanvas::setPassword(const jukebox::Password* password_)
{
    togglePassword->setToggleState(true, dontSendNotification);
    buttonChangePassword->setEnabled(true);
    password = password_;
}

void SetupPageCanvas::turnOffPassword()
{
    toggleNoPassword->setToggleState(true, dontSendNotification);
    buttonChangePassword->setEnabled(false);
    password = nullptr;
}

void SetupPageCanvas::showChangePasswordDialog()
{
    juce::String title = password != nullptr ? "Change password" : "New password";
    juce::String dialogText = password != nullptr ? "To change password please enter the old one and twice the new password" :
                                                    "To set new password please enter the new password twice";
    AlertWindow passwordDialog(title,
                               dialogText,
                               AlertWindow::QuestionIcon);

    if(password != nullptr)
        passwordDialog.addTextEditor ("oldPassword", "", "Old password:", true);

    passwordDialog.addTextEditor ("newPassword", "", "New password:", true);
    passwordDialog.addTextEditor ("secondPassword", "", "New password again:", true);
    passwordDialog.addButton ("OK",     1, KeyPress (KeyPress::returnKey, 0, 0));
    passwordDialog.addButton ("Cancel", 0, KeyPress (KeyPress::escapeKey, 0, 0));

    bool canQuit = false;
    while(!canQuit)
    {
        if (passwordDialog.runModalLoop() == 0)
        {
            canQuit = true;
            continue;
        }

        if(password != nullptr)
        {
            auto text = passwordDialog.getTextEditorContents("oldPassword");
            if(!password->isMatching(text))
            {
                AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                                            "Wrong password",
                                            "Wrong password was given!");
                continue;
            }
        }

        auto newPassword = passwordDialog.getTextEditorContents("newPassword");
        auto secondPassword = passwordDialog.getTextEditorContents("secondPassword");

        if(newPassword.isEmpty())
        {
            AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                                        "Empty password",
                                        "Empty password is not allowed!");
            continue;
        }

        if(newPassword.compare(secondPassword) != 0)
        {
            AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                                        "Mismatching passwords",
                                        "The two password are not matching!");
            continue;
        }

        jukebox::Password pw(newPassword);
        passwordChangedSignal(pw);

        canQuit = true;
    }
}

void SetupPageCanvas::handleNoPasswordToggle()
{
    if(password == nullptr)
        return;

    AlertWindow passwordDialog("Password check",
                               "To turn off password please enter the old password",
                               AlertWindow::WarningIcon);

    passwordDialog.addTextEditor ("text", "", "Password:", true);
    passwordDialog.addButton ("OK",     1, KeyPress (KeyPress::returnKey, 0, 0));
    passwordDialog.addButton ("Cancel", 0, KeyPress (KeyPress::escapeKey, 0, 0));

    if (passwordDialog.runModalLoop() != 0)
    {
        auto text = passwordDialog.getTextEditorContents("text");
        if(!password->isMatching(text))
        {
            AlertWindow::showMessageBox(AlertWindow::WarningIcon,
                                        "Wrong password",
                                        "Wrong password was given!");

            togglePassword->setToggleState(true, dontSendNotification);
            return;
        }

        passwordTurnedOffSignal();
    }
}

void SetupPageCanvas::handlePasswordToggle()
{
    if(password != nullptr)
        return;

    showChangePasswordDialog();

    if(password == nullptr)
    {
        toggleNoPassword->setToggleState(true, dontSendNotification);
    }
    else
    {
        buttonChangePassword->setEnabled(true);
    }
}
