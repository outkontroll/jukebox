#include "SetupPage.h"
#include "SetupPagePositionCalculator.h"

namespace jukebox::gui {
class TimeToPlayASongListener : public juce::ComboBox::Listener
{
public:
    TimeToPlayASongListener(SetupPage&);
    void comboBoxChanged(juce::ComboBox*) override;
private:
    SetupPage& ownerPage;
};

class TimeToSaveInsertedCoinsListener : public juce::ComboBox::Listener
{
public:
    TimeToSaveInsertedCoinsListener(SetupPage&);
    void comboBoxChanged(juce::ComboBox*) override;
private:
    SetupPage& ownerPage;
};
}

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
    comboTimeToPlayASong->addListener(timeToPlayASongListener = new TimeToPlayASongListener(*this));

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
    comboTimeToSaveInsertedCoins->addListener(timeToSaveInsertedCoinsListener = new TimeToSaveInsertedCoinsListener(*this));
}

SetupPage::~SetupPage()
{
    infoStatistics = nullptr;
    txtStatistics = nullptr;
    infoTimeToPlayASong = nullptr;
    comboTimeToPlayASong = nullptr;
    infoTimeToSaveInsertedCoins = nullptr;
    comboTimeToSaveInsertedCoins = nullptr;
    timeToPlayASongListener = nullptr;
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
    textPlace = SetupPagePositionCalculator{}.calculateTextPlace(getWidth(), getHeight(), bigFontSize);
    infoStatistics->setBounds(10, 66, 100, 24);
    txtStatistics->setBounds(10, 102, 600, 400);
    infoTimeToPlayASong->setBounds(10, 538, 250, 24);
    comboTimeToPlayASong->setBounds(276, 538, 40, 24);
    infoTimeToSaveInsertedCoins->setBounds(10, 574, 250, 24);
    comboTimeToSaveInsertedCoins->setBounds(266, 574, 50, 24);
}

void SetupPage::setTimeToPlayASong(int millisecs)
{
    comboTimeToPlayASong->setSelectedId(millisecs / 1000 + 1, dontSendNotification);
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

void SetupPage::setTimeToSaveInsertedCoins(int millisecs)
{
    comboTimeToSaveInsertedCoins->setSelectedId(getSelectedIndexFromSaveInsertedCoinHours(millisecs / (1000 * 3600)), dontSendNotification);
}

void SetupPage::showStatistics(const std::string& statistics)
{
    txtStatistics->setText(statistics);
}

TimeToPlayASongListener::TimeToPlayASongListener(SetupPage& owner) :
    ownerPage(owner)
{
}

void TimeToPlayASongListener::comboBoxChanged(ComboBox* combo)
{
    ownerPage.timeToPlayASongChangedSignal((combo->getSelectedId() - 1) * 1000);
}

TimeToSaveInsertedCoinsListener::TimeToSaveInsertedCoinsListener(SetupPage& owner) :
    ownerPage(owner)
{
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

void TimeToSaveInsertedCoinsListener::comboBoxChanged(ComboBox* combo)
{
    ownerPage.timeToSaveInsertedCoinsChangedSignal(getSaveInsertedCoinHoursFromSelected(combo->getSelectedId()) * 3600 * 1000);
}
