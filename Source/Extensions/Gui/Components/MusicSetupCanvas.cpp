#include "MusicSetupCanvas.h"
#include "MusicSetupCanvasPositionCalculator.h"

namespace jukebox { namespace gui {
class MusicDirectoryListener : public juce::Button::Listener
{
public:
    MusicDirectoryListener(MusicSetupCanvas& owner);
    void buttonClicked(juce::Button*) override;
private:
    MusicSetupCanvas& ownerPage;
};
}}

using namespace jukebox::gui;
using namespace juce;

namespace {
    const float bigFontSize = 24.0f;
    const char* pageName = "Music Setup";
}

MusicSetupCanvas::MusicSetupCanvas()
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
    txtMusicDirectory->setEscapeAndReturnKeysConsumed(false);

    addAndMakeVisible(buttonMusicDirectory = new TextButton("music directory button"));
    buttonMusicDirectory->setButtonText("...");
    buttonMusicDirectory->addListener(musicDirectoryListener = new MusicDirectoryListener(*this));

    directoryThread.startThread (1);
    addAndMakeVisible(treeMusicDir = new FileTreeComponent(listToShow));
    treeMusicDir->setColour(TreeView::backgroundColourId, Colours::white);
    treeMusicDir->addListener(this);

    addAndMakeVisible(imagePreview);
}

MusicSetupCanvas::~MusicSetupCanvas()
{
    treeMusicDir->removeListener(this);

    infoMusicDirectory = nullptr;
    txtMusicDirectory = nullptr;
    buttonMusicDirectory = nullptr;
    musicDirectoryListener = nullptr;
    treeMusicDir = nullptr;
}

void MusicSetupCanvas::paint(Graphics& g)
{
    setWantsKeyboardFocus(true);
    grabKeyboardFocus();

    g.setColour(Colours::black);
    g.drawRect(Rectangle<int>{0, 0, getWidth(), getHeight()});

    g.setFont(bigFontSize);

    // album's number
    g.drawText(pageName, textPlace, Justification::centredLeft);
}

void MusicSetupCanvas::parentSizeChanged()
{
    textPlace = MusicSetupCanvasPositionCalculator{}.calculateTextPlace(getWidth(), getHeight(), bigFontSize);
    infoMusicDirectory->setBounds(10, 30, 100, 24);
    txtMusicDirectory->setBounds(116, 30, 450, 24);
    buttonMusicDirectory->setBounds(578, 30, 36, 24);
    treeMusicDir->setBounds(636, 30, 400, 400);
    imagePreview.setBounds(636, 450, 300, 300);
}

void MusicSetupCanvas::setMusicDirectory(const std::string& musicDirectory)
{
    txtMusicDirectory->setText(musicDirectory);
    listToShow.setDirectory(juce::File(musicDirectory), true, true);
}

void MusicSetupCanvas::selectionChanged()
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

bool MusicSetupCanvas::isImageFile(const File& file) const
{
    return file.existsAsFile() && file.getFileExtension().containsWholeWord("jpg");
}

MusicDirectoryListener::MusicDirectoryListener(MusicSetupCanvas& owner) :
    ownerPage(owner)
{
}

void MusicDirectoryListener::buttonClicked(Button*)
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

    ownerPage.lostFocusSignal();
}
