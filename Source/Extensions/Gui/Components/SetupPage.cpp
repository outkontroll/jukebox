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

    directoryThread.startThread (1);
    addAndMakeVisible(treeMusicDir = new FileTreeComponent(listToShow));
    treeMusicDir->setColour(TreeView::backgroundColourId, Colours::white);
    treeMusicDir->addListener(this);

    addAndMakeVisible(imagePreview);
}

SetupPage::~SetupPage()
{
    treeMusicDir->removeListener(this);

    infoMusicDirectory = nullptr;
    txtMusicDirectory = nullptr;
    buttonMusicDirectory = nullptr;
    infoStatistics = nullptr;
    txtStatistics = nullptr;
    infoTimeToPlayASong = nullptr;
    comboTimeToPlayASong = nullptr;
    infoTimeToSaveInsertedCoins = nullptr;
    comboTimeToSaveInsertedCoins = nullptr;
    musicDirectoryListener = nullptr;
    timeToPlayASongListener = nullptr;
    treeMusicDir = nullptr;
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
    infoMusicDirectory->setBounds(10, 30, 100, 24);
    txtMusicDirectory->setBounds(116, 30, 450, 24);
    buttonMusicDirectory->setBounds(578, 30, 36, 24);
    infoStatistics->setBounds(10, 66, 100, 24);
    txtStatistics->setBounds(10, 102, 600, 400);
    infoTimeToPlayASong->setBounds(10, 538, 250, 24);
    comboTimeToPlayASong->setBounds(276, 538, 40, 24);
    infoTimeToSaveInsertedCoins->setBounds(10, 574, 250, 24);
    comboTimeToSaveInsertedCoins->setBounds(266, 574, 50, 24);
    treeMusicDir->setBounds(636, 30, 400, 400);
    imagePreview.setBounds(636, 450, 300, 300);
}

void SetupPage::setMusicDirectory(const std::string& musicDirectory)
{
    txtMusicDirectory->setText(musicDirectory);
    listToShow.setDirectory(juce::File(musicDirectory), true, true);
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

juce::Rectangle<float> SetupPage::calculateTextPlace(float width, float height) const
{
    const float xPosition = width / 2;
    const float yPosition = height / 3;
    const float textHeight = bigFontSize;
    const float textWidth = width;

    return { xPosition, yPosition, textWidth, textHeight };
}

void SetupPage::selectionChanged()
{
    auto selectedFile = treeMusicDir->getSelectedFile();

    if(isImageFile(selectedFile))
    {
        imagePreview.setImage (juce::ImageCache::getFromFile (selectedFile));
        if(!imagePreview.isVisible())
            imagePreview.setVisible(true);
    }
    else
    {
        imagePreview.setVisible(false);
    }
}

bool SetupPage::isImageFile(const File& file) const
{
    return file.existsAsFile() && file.getFileExtension().containsWholeWord("jpg");
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

SetupPage::TimeToSaveInsertedCoinsListener::TimeToSaveInsertedCoinsListener(SetupPage& owner) :
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

void SetupPage::TimeToSaveInsertedCoinsListener::comboBoxChanged(ComboBox* combo)
{
    ownerPage.timeToSaveInsertedCoinsChangedSignal(getSaveInsertedCoinHoursFromSelected(combo->getSelectedId()) * 3600 * 1000);
}
