#include "MusicSetupCanvas.h"
#include "MusicSetupCanvasPositionCalculator.h"
#include "Song.h"
#include "StdAddons.hpp"

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

    addChildComponent(infoArtist = new Label("artist label", "Artist"));
    infoArtist->setFont (Font (smallFontSize, Font::plain));
    infoArtist->setJustificationType (Justification::centredLeft);
    infoArtist->setEditable (false, false, false);
    infoArtist->setColour (TextEditor::textColourId, Colours::black);
    infoArtist->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addChildComponent(txtArtist = new TextEditor("artist text"));
    txtArtist->setFont(Font(smallFontSize, Font::plain));
    txtArtist->setMultiLine(false);
    txtArtist->setReturnKeyStartsNewLine(false);
    txtArtist->setReadOnly(true);
    txtArtist->setScrollbarsShown(false);
    txtArtist->setCaretVisible(false);
    txtArtist->setPopupMenuEnabled(true);
    txtArtist->setText(String());
    txtArtist->setEscapeAndReturnKeysConsumed(false);

    addChildComponent(infoTitle = new Label("title label", "Title"));
    infoTitle->setFont (Font (smallFontSize, Font::plain));
    infoTitle->setJustificationType (Justification::centredLeft);
    infoTitle->setEditable (false, false, false);
    infoTitle->setColour (TextEditor::textColourId, Colours::black);
    infoTitle->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addChildComponent(txtTitle = new TextEditor("title text"));
    txtTitle->setFont(Font(smallFontSize, Font::plain));
    txtTitle->setMultiLine(false);
    txtTitle->setReturnKeyStartsNewLine(false);
    txtTitle->setReadOnly(true);
    txtTitle->setScrollbarsShown(false);
    txtTitle->setCaretVisible(false);
    txtTitle->setPopupMenuEnabled(true);
    txtTitle->setText(String());
    txtTitle->setEscapeAndReturnKeysConsumed(false);

    addChildComponent(infoSongNames = new Label("song names label", "Song names"));
    infoSongNames->setFont (Font (smallFontSize, Font::plain));
    infoSongNames->setJustificationType (Justification::centredLeft);
    infoSongNames->setEditable (false, false, false);
    infoSongNames->setColour (TextEditor::textColourId, Colours::black);
    infoSongNames->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addChildComponent(txtSongNames = new TextEditor("song names text"));
    txtSongNames->setFont(Font(smallFontSize, Font::plain));
    txtSongNames->setMultiLine(true);
    txtSongNames->setReturnKeyStartsNewLine(false);
    txtSongNames->setReadOnly(true);
    txtSongNames->setScrollbarsShown(true);
    txtSongNames->setCaretVisible(false);
    txtSongNames->setPopupMenuEnabled(true);
    txtSongNames->setText(String());
    txtSongNames->setEscapeAndReturnKeysConsumed(false);
}

MusicSetupCanvas::~MusicSetupCanvas()
{
    treeMusicDir->removeListener(this);
    buttonImport->removeListener(this);
    buttonMusicDirectory->removeListener(this);

    infoMusicDirectory = nullptr;
    txtMusicDirectory = nullptr;
    buttonMusicDirectory = nullptr;
    buttonImport = nullptr;
    treeMusicDir = nullptr;
    infoArtist = nullptr;
    txtArtist = nullptr;
    infoTitle = nullptr;
    txtTitle = nullptr;
    infoSongNames = nullptr;
    txtSongNames = nullptr;
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
    infoArtist->setBounds(calc.calculateInfoArtistBounds());
    txtArtist->setBounds(calc.calculateTextArtistBounds());
    infoTitle->setBounds(calc.calculateInfoTitleBounds());
    txtTitle->setBounds(calc.calculateTextTitleBounds());
    infoSongNames->setBounds(calc.calculateInfoSongsBounds());
    txtSongNames->setBounds(calc.calculateTextSongsBounds());
}

void MusicSetupCanvas::setMusicDirectory(const std::string& musicDirectory)
{
    txtMusicDirectory->setText(musicDirectory);
    listToShow.setDirectory(juce::File(musicDirectory), true, true);
}

void MusicSetupCanvas::setAlbumsForMusicSetup(const std::vector<jukebox::audio::AlbumInfo>& albums_)
{
    albums = &albums_;
    listToShow.refresh();
    treeMusicDir->refresh();
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

    if(parentDir.isDirectory() &&
       parentDir != currentVisibleDirectory)
    {
        currentVisibleDirectory = parentDir;
        loadImage(albumInfo);
        loadTextFile(albumInfo);
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

        requestToImportAlbumSignal(name.toStdString());
    }
}

void MusicSetupCanvas::loadImage(const AlbumInfo& albumInfo)
{
    if(!albumInfo.imagePath.empty())
    {

        imagePreview.setImage (ImageCache::getFromFile(File(albumInfo.imagePath)));
        if(!imagePreview.isVisible())
            imagePreview.setVisible(true);
    }
    else
    {
        imagePreview.setVisible(false);
    }
}

void MusicSetupCanvas::loadTextFile(const audio::AlbumInfo& albumInfo)
{
    if(!albumInfo.textFilePath.empty())
    {
        txtArtist->setText(albumInfo.artist);
        txtTitle->setText(albumInfo.title);

        const auto songNames = std_addons::accumulate(albumInfo.songs, String{""}, [](const String& text, const Song& song){
           return text + song.visibleName + "\n";
        }).trimEnd();
        txtSongNames->setText(songNames);

        infoArtist->setVisible(true);
        txtArtist->setVisible(true);
        infoTitle->setVisible(true);
        txtTitle->setVisible(true);
        infoSongNames->setVisible(true);
        txtSongNames->setVisible(true);
    }
    else
    {
        infoArtist->setVisible(false);
        txtArtist->setVisible(false);
        infoTitle->setVisible(false);
        txtTitle->setVisible(false);
        infoSongNames->setVisible(false);
        txtSongNames->setVisible(false);
    }

}
