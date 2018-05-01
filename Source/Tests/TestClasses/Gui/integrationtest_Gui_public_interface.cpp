#include "gtest/gtest.h"
#include "MainComponentMock.h"
#include "FileSystemMock.h"
#include "GuiTester.h"
#include "Song.h"
#include "ResourceId.h"
#include "ResourceString.h"

using namespace jukebox;
using namespace jukebox::gui;
using namespace jukebox::audio;
using namespace testing;

namespace {
    const auto setMusicDir = "fakeMusicDir";
    constexpr unsigned int testCredits = 12;
    constexpr int defaultSelectedAlbumIndex = 1;
    constexpr int defaultSelectedSongIndex = 0;
}

class GuiTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        auto mainCompMock = std::make_unique<StrictMock<MainComponentMock>>();
        mainComponentMock = mainCompMock.get();
        auto filesysMock = std::make_unique<NiceMock<FileSystemMock>>();
        fileSystemMock = filesysMock.get();
        gui = std::make_unique<GuiTester>(std::move(mainCompMock), std::move(filesysMock));
        gui->setFileSystem(fileSystemMock);
    }

    std::unique_ptr<GuiTester> gui;
    StrictMock<MainComponentMock>* mainComponentMock;
    NiceMock<FileSystemMock>* fileSystemMock;

    jukebox::signals::Slot eventsSlot;
};

// public interface

TEST_F(GuiTest, WhenRefreshCreditsCalled_ThenSameIsCalledOnMainComponentWithSameParameter)
{
    EXPECT_CALL(*mainComponentMock, refreshCredits(testCredits));

    gui->refreshCredits(testCredits);
}

TEST_F(GuiTest, WhenShowStatusMessageIsCalledWithResourceId_ThenTheSameIsCalledOnMainComponentWithTranslatedString)
{
    const juce::String translatedStringPlaying(Resources::getResourceStringFromId(ResourceId::WarningNotPlayingSong));
    EXPECT_CALL(*mainComponentMock, showStatusMessage(translatedStringPlaying));

    gui->showStatusMessage(ResourceId::WarningNotPlayingSong);
}

TEST_F(GuiTest, WhenSetMusicFolderIsCalled_ThenGuiCallsLoadSingleAndMultipleAlbumsAndUpdateSelection)
{
    EXPECT_CALL(*mainComponentMock, setMusicDirectory(setMusicDir));
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(setMusicDir, defaultSelectedAlbumIndex, _));
    EXPECT_CALL(*mainComponentMock, loadMultipleAlbums(setMusicDir, defaultSelectedAlbumIndex, _));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(defaultSelectedAlbumIndex));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex));

    gui->setMusicFolder(setMusicDir);
}

TEST_F(GuiTest, WhenSetTimeToPlaySongIsCalled_ThenTheSameIsCalledOnMainComponent)
{
    EXPECT_CALL(*mainComponentMock, setTimeToPlayASong(2000));

    gui->setTimeToPlaySong(2000);
}

TEST_F(GuiTest, WhenSetCurrentlyPlayedSongIsCalled_ThenTheSameAndStatusUpdateIsCalledOnMainComponent)
{
    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*mainComponentMock, setCurrentlyPlayedSong(song));
    const juce::String translatedStringPlaying(Resources::getResourceStringFromId(ResourceId::Playing));
    EXPECT_CALL(*mainComponentMock, showStatusMessage(translatedStringPlaying));

    gui->setCurrentlyPlayedSong(song);
}

TEST_F(GuiTest, WhenEnqueueIsCalled_ThenTheSameIsCalledOnMainComponent)
{
    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*mainComponentMock, enqueue(song));

    gui->enqueue(song);
}

TEST_F(GuiTest, WhenRemoveCurrentSongIsCalled_ThenTheSameIsCalledOnMainComponent)
{
    EXPECT_CALL(*mainComponentMock, removeCurrentSong());

    gui->removeCurrentSong();
}

TEST_F(GuiTest, WhenShowStatisticsIsCalled_ThenTheSameIsCalledOnMainComponent)
{
    std::string statistics("fakeStat");
    EXPECT_CALL(*mainComponentMock, showStatistics(statistics));

    gui->showStatistics(statistics);
}

TEST_F(GuiTest, WhenPrepareForExitIsCalled_ThenTheSameIsCalledOnMainComponent)
{
    EXPECT_CALL(*mainComponentMock, prepareForExit());

    gui->prepareForExit();
}