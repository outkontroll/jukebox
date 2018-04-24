#include "SetupPage.h"

using namespace jukebox::gui;
using namespace juce;

namespace {
    const float bigFontSize = 24.0f;
    const char* setupPageName = "Setup";
}

SetupPage::SetupPage()
{
    addAndMakeVisible(infoMusicDirectory = new Label("music directory info label", "Music directory:"));
    infoMusicDirectory->setFont (Font (15.00f, Font::plain));
    infoMusicDirectory->setJustificationType (Justification::centredLeft);
    infoMusicDirectory->setEditable (false, false, false);
    infoMusicDirectory->setColour (TextEditor::textColourId, Colours::black);
    infoMusicDirectory->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible(txtMusicDirectory = new TextEditor("music directory text"));
    txtMusicDirectory->setMultiLine(false);
    txtMusicDirectory->setReturnKeyStartsNewLine(false);
    txtMusicDirectory->setReadOnly(true);
    txtMusicDirectory->setScrollbarsShown(false);
    txtMusicDirectory->setCaretVisible(false);
    txtMusicDirectory->setPopupMenuEnabled(true);
    txtMusicDirectory->setText(String());

    addAndMakeVisible(buttonMusicDirectory = new TextButton("music directory button"));
    buttonMusicDirectory->setButtonText("...");
    buttonMusicDirectory->addListener(musicDirectoryListener = new MusicDirectoryListener(*this));

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
}

SetupPage::~SetupPage()
{
    infoMusicDirectory = nullptr;
    txtMusicDirectory = nullptr;
    buttonMusicDirectory = nullptr;
    infoStatistics = nullptr;
    txtStatistics = nullptr;
    infoTimeToPlayASong = nullptr;
    comboTimeToPlayASong = nullptr;
    musicDirectoryListener = nullptr;
    timeToPlayASongListener = nullptr;
}

void SetupPage::paint(Graphics& g)
{
    //TODO just for testing purposes
    g.setColour(Colours::aliceblue);
    g.drawRect(Rectangle<int>{0, 0, getWidth(), getHeight()});
    //END TODO

    g.setColour(Colours::black);

    auto currentFont = g.getCurrentFont();
    currentFont.setHeight(bigFontSize);
    g.setFont(currentFont);

    // album's number
    g.drawText(setupPageName, textPlace, Justification::centredLeft);
}

void SetupPage::parentSizeChanged()
{
    textPlace = calculateTextPlace(getWidth(), getHeight());
    infoMusicDirectory->setBounds(10, 60, 100, 24);
    txtMusicDirectory->setBounds(116, 60, 450, 24);
    buttonMusicDirectory->setBounds(578, 60, 36, 24);
    infoStatistics->setBounds(10, 96, 100, 24);
    txtStatistics->setBounds(10, 132, 600, 400);
    infoTimeToPlayASong->setBounds(10, 568, 200, 24);
    comboTimeToPlayASong->setBounds(216, 568, 36, 24);
}

void SetupPage::setMusicDirectory(const std::string& musicDirectory)
{
    txtMusicDirectory->setText(musicDirectory);
}

void SetupPage::setTimeToPlayASong(int millisecs)
{
    comboTimeToPlayASong->setSelectedId(millisecs / 1000 + 1, dontSendNotification);
}

void SetupPage::showStatistics(const std::string& statistics)
{
    txtStatistics->setText(statistics);
}

juce::Rectangle<float> SetupPage::calculateTextPlace(float width, float height) const
{
    const float xPosition = width / 2;
    const float yPosition = height / 3;
    const float textHeight = bigFontSize;
    const float textWidth = width;

    return { xPosition, yPosition, textWidth, textHeight };
}

SetupPage::MusicDirectoryListener::MusicDirectoryListener(SetupPage& owner) :
    ownerPage(owner)
{
}

void SetupPage::MusicDirectoryListener::buttonClicked(Button*)
{
    auto fc = FileChooser("Choose a music directory...",
                          File(ownerPage.txtMusicDirectory->getText()),
                          "*",
                          true);
    if(fc.showDialog(FileBrowserComponent::openMode | FileBrowserComponent::canSelectDirectories, nullptr))
    {
        auto result = fc.getResult();
        auto name = result.isDirectory() ? result.getFullPathName()
                                         : result.getParentDirectory().getFullPathName();

        ownerPage.musicDirectoryChangedSignal(name.toStdString());
    }
}

SetupPage::TimeToPlayASongListener::TimeToPlayASongListener(SetupPage& owner) :
    ownerPage(owner)
{
}

void SetupPage::TimeToPlayASongListener::comboBoxChanged(ComboBox* combo)
{
    ownerPage.timeToPlayASongChangedSignal((combo->getSelectedId() - 1) * 1000);
}
