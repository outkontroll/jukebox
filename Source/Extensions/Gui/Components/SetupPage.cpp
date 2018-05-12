#include "SetupPage.h"
#include "SetupPagePositionCalculator.h"
#include "Password.h"

using namespace jukebox::gui;
using namespace juce;

namespace {
    const float bigFontSize = 24.0f;
    const char* setupPageName = "Setup";
}

int getSelectedIndexFromSaveInsertedCoinHours(int SaveInsertedCoinHours);
int getSaveInsertedCoinHoursFromSelected(int selectedIndex);

SetupPage::SetupPage()
{
    addAndMakeVisible(infoStatistics = new Label("statistics info label", "Statistics:"));
    infoStatistics->setFont (Font (15.00f, Font::plain));
    infoStatistics->setJustificationType (Justification::centredLeft);
    infoStatistics->setEditable (false, false, false);
    infoStatistics->setColour (TextEditor::textColourId, Colours::black);
    infoStatistics->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible(txtStatistics = new TextEditor("statistics text"));
    txtStatistics->setMultiLine(true);
    txtStatistics->setReturnKeyStartsNewLine(false);
    txtStatistics->setReadOnly(true);
    txtStatistics->setScrollbarsShown(true);
    txtStatistics->setCaretVisible(false);
    txtStatistics->setPopupMenuEnabled(true);
    txtStatistics->setText(String());

    addAndMakeVisible(infoTimeToPlayASong = new Label("time to play a song label", "Seconds to cancel playing a song"));
    infoTimeToPlayASong->setFont (Font (15.00f, Font::plain));
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
    infoTimeToSaveInsertedCoins->setFont (Font (15.00f, Font::plain));
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

    addAndMakeVisible(buttonChangePassword = new TextButton("change password button"));
    buttonChangePassword->setButtonText("Change password");
    buttonChangePassword->addListener(this);

    addAndMakeVisible(toggleNoPassword = new ToggleButton("toggle no password"));
    toggleNoPassword->setRadioGroupId(12);
    toggleNoPassword->addListener(this);

    addAndMakeVisible(togglePassword = new ToggleButton("toggle password"));
    togglePassword->setRadioGroupId(12);
    togglePassword->addListener(this);
}

SetupPage::~SetupPage()
{
    comboTimeToPlayASong->removeListener(this);
    comboTimeToSaveInsertedCoins->removeListener(this);
    buttonChangePassword->removeListener(this);
    toggleNoPassword->removeListener(this);
    togglePassword->removeListener(this);

    infoStatistics = nullptr;
    txtStatistics = nullptr;
    infoTimeToPlayASong = nullptr;
    comboTimeToPlayASong = nullptr;
    infoTimeToSaveInsertedCoins = nullptr;
    comboTimeToSaveInsertedCoins = nullptr;
    buttonChangePassword = nullptr;
    toggleNoPassword = nullptr;
    togglePassword = nullptr;
}

void SetupPage::paint(Graphics& g)
{
    g.setColour(Colours::black);
    g.drawRect(Rectangle<int>{0, 0, getWidth(), getHeight()});

    g.setFont(bigFontSize);

    // album's number
    g.drawText(setupPageName, textPlace, Justification::centredLeft);
}

void SetupPage::parentSizeChanged()
{
    SetupPagePositionCalculator calc{getWidth(), getHeight(), bigFontSize};

    textPlace = calc.calculateTextPlace();
    infoStatistics->setBounds(10, 66, 100, 24);
    txtStatistics->setBounds(calc.calculateStatisticsBounds());
    infoTimeToPlayASong->setBounds(10, 538, 250, 24);
    comboTimeToPlayASong->setBounds(276, 538, 40, 24);
    infoTimeToSaveInsertedCoins->setBounds(10, 574, 250, 24);
    comboTimeToSaveInsertedCoins->setBounds(266, 574, 50, 24);
    buttonChangePassword->setBounds(calc.calculateChangePasswordBounds());
    toggleNoPassword->setBounds(calc.calculateNoPasswordToggleBounds());
    togglePassword->setBounds(calc.calculatePasswordToggleBounds());
}

void SetupPage::buttonClicked(Button* button)
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

void SetupPage::comboBoxChanged(ComboBox* combo)
{
    if(combo == comboTimeToPlayASong)
    {
        timeToPlayASongChangedSignal((combo->getSelectedId() - 1) * 1000);
    }
    else if(combo == comboTimeToSaveInsertedCoins)
    {
        timeToSaveInsertedCoinsChangedSignal(getSaveInsertedCoinHoursFromSelected(combo->getSelectedId()) * 3600 * 1000);
    }
}

void SetupPage::setTimeToPlayASong(int millisecs)
{
    comboTimeToPlayASong->setSelectedId(millisecs / 1000 + 1, dontSendNotification);
}

void SetupPage::setTimeToSaveInsertedCoins(int millisecs)
{
    comboTimeToSaveInsertedCoins->setSelectedId(getSelectedIndexFromSaveInsertedCoinHours(millisecs / (1000 * 3600)), dontSendNotification);
}

void SetupPage::showStatistics(const std::string& statistics)
{
    txtStatistics->setText(statistics);
}

void SetupPage::setPassword(const jukebox::Password* password_)
{
    togglePassword->setToggleState(true, dontSendNotification);
    buttonChangePassword->setEnabled(true);
    password = password_;
}

void SetupPage::turnOffPassword()
{
    toggleNoPassword->setToggleState(true, dontSendNotification);
    buttonChangePassword->setEnabled(false);
    password = nullptr;
}

void SetupPage::showChangePasswordDialog()
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

void SetupPage::handleNoPasswordToggle()
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

void SetupPage::handlePasswordToggle()
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
