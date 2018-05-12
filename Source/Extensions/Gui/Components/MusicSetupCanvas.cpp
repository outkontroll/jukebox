#include "MusicSetupCanvas.h"
#include "MusicSetupCanvasPositionCalculator.h"
#include "Song.h"

using namespace jukebox::gui;
using namespace jukebox::audio;
using namespace juce;

namespace {
    const float bigFontSize = 24.0f;
    const float smallFontSize = 18.0f;
}

MusicSetupCanvas::MusicSetupCanvas()
{
    addAndMakeVisible(infoMusicDirectory = new Label("music directory info label", "Music directory:"));
    infoMusicDirectory->setFont (Font (smallFontSize, Font::plain));
    infoMusicDirectory->setJustificationType (Justification::centredLeft);
    infoMusicDirectory->setEditable (false, false, false);
    infoMusicDirectory->setColour (TextEditor::textColourId, Colours::black);
    infoMusicDirectory->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible(txtMusicDirectory = new TextEditor("music directory text"));
    txtMusicDirectory->setFont(Font(smallFontSize, Font::plain));
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
    buttonMusicDirectory->addListener(this);

    addAndMakeVisible(buttonImport = new TextButton("import button"));
    buttonImport->setButtonText("Import music");
    buttonImport->addListener(this);

    directoryThread.startThread (1);
    addAndMakeVisible(treeMusicDir = new FileTreeComponent(listToShow));
    treeMusicDir->setColour(TreeView::backgroundColourId, Colours::white);
    treeMusicDir->addListener(this);

    addAndMakeVisible(imagePreview);
    imagePreview.setImagePlacement(RectanglePlacement(RectanglePlacement::stretchToFit));
}

MusicSetupCanvas::~MusicSetupCanvas()
{
    treeMusicDir->removeListener(this);

    infoMusicDirectory = nullptr;
    txtMusicDirectory = nullptr;
    buttonMusicDirectory = nullptr;
    buttonImport = nullptr;
    treeMusicDir = nullptr;
}

void MusicSetupCanvas::paint(Graphics& g)
{
    setWantsKeyboardFocus(true);
    grabKeyboardFocus();

    g.setColour(Colours::black);
    g.drawRect(Rectangle<int>{0, 0, getWidth(), getHeight()});

    g.setFont(bigFontSize);
}

void MusicSetupCanvas::parentSizeChanged()
{
    MusicSetupCanvasPositionCalculator calc{getWidth(), getHeight(), bigFontSize};

    infoMusicDirectory->setBounds(calc.calculateInfoMusicDirectoryBounds());
    txtMusicDirectory->setBounds(calc.calculateTextMusicDirectoryBounds());
    buttonMusicDirectory->setBounds(calc.calculateButtonMusicDirectoryBounds());
    treeMusicDir->setBounds(calc.calculateTreeMusicDirectoryBounds());
    buttonImport->setBounds(calc.calculateButtonImportBounds());
    imagePreview.setBounds(calc.calculateImagePreviewBounds());
}

void MusicSetupCanvas::setMusicDirectory(const std::string& musicDirectory)
{
    txtMusicDirectory->setText(musicDirectory);
    listToShow.setDirectory(juce::File(musicDirectory), true, true);
}

void MusicSetupCanvas::setAlbumsForMusicSetup(const std::vector<jukebox::audio::AlbumInfo>& albums_)
{
    albums = &albums_;
}

void MusicSetupCanvas::buttonClicked(Button* button)
{
    if(button == buttonMusicDirectory)
        selectMusicDirectory();
    else if(button == buttonImport)
        importMusicDirectory();
}

void MusicSetupCanvas::selectionChanged()
{
    if(albums == nullptr)
        return;

    auto selectedFile = treeMusicDir->getSelectedFile();
    const auto parentDir = selectedFile.isDirectory() ? selectedFile : selectedFile.getParentDirectory();

    const auto albumId = [&]() -> unsigned int {
        try
        {
            return static_cast<unsigned int>(std::stoi(parentDir.getFileName().toStdString()));
        }
        catch(std::exception&)
        {
            return 0;
        }
    }();

    if(albumId == 0 ||
       albumId > albums->size())
        return;

    const AlbumInfo& albumInfo = albums->at(albumId - 1);

    if(!albumInfo.imagePath.empty())
    {
        if(parentDir.isDirectory() &&
           parentDir != currentVisibleDirectory)
        {
            currentVisibleDirectory = parentDir;
            imagePreview.setImage (juce::ImageCache::getFromFile (juce::File(albumInfo.imagePath)));
            if(!imagePreview.isVisible())
                imagePreview.setVisible(true);
        }
    }
    else
    {
        if(parentDir.isDirectory() &&
           parentDir != currentVisibleDirectory)
            imagePreview.setVisible(false);
    }
}

void MusicSetupCanvas::selectMusicDirectory()
{
    auto fc = FileChooser("Choose a music directory...",
                          File(txtMusicDirectory->getText()),
                          "*",
                          true);
    if(fc.showDialog(FileBrowserComponent::openMode | FileBrowserComponent::canSelectDirectories, nullptr))
    {
        auto result = fc.getResult();
        auto name = result.isDirectory() ? result.getFullPathName()
                                         : result.getParentDirectory().getFullPathName();

        musicDirectoryChangedSignal(name.toStdString());
    }

    lostFocusSignal();
}

bool MusicSetupCanvas::isImageFile(const File& file) const
{
    return file.existsAsFile() && file.getFileExtension().containsWholeWord("jpg");
}

void MusicSetupCanvas::importMusicDirectory()
{
    auto fc = FileChooser("Choose a music directory to import...",
                          File::getSpecialLocation(File::userMusicDirectory),
                          "*",
                          true);
    if(fc.showDialog(FileBrowserComponent::openMode | FileBrowserComponent::canSelectDirectories, nullptr))
    {
        auto result = fc.getResult();
        auto name = result.isDirectory() ? result.getFullPathName()
                                         : result.getParentDirectory().getFullPathName();

        name.toStdString();
    }
}
