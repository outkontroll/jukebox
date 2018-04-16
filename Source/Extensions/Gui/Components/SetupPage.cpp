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
}

SetupPage::~SetupPage()
{
    infoMusicDirectory = nullptr;
    txtMusicDirectory = nullptr;
    buttonMusicDirectory = nullptr;
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
    txtMusicDirectory->setBounds(116, 60, 200, 24);
    buttonMusicDirectory->setBounds(328, 60, 36, 24);
}

void SetupPage::setMusicDirectory(const std::string& musicDirectory)
{
    txtMusicDirectory->setText(musicDirectory);
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
                          File::getCurrentWorkingDirectory(),
                          "*",
                          true);
    fc.showDialog(FileBrowserComponent::openMode | FileBrowserComponent::canSelectDirectories, nullptr);
    auto result = fc.getResult();
    auto name = result.isDirectory() ? result.getFullPathName()
                                     : result.getParentDirectory().getFullPathName();

    ownerPage.musicDirectoryChangedSignal(name.toStdString());
}
