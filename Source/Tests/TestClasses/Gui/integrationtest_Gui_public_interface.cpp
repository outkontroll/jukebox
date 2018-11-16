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
    const std::vector<AlbumInfo> fakeAlbums16(16, {{{}, {}, {}}, "", "", "", "", 1});
}

TEST(GuiTest1, baseClassCtorDtor)
{
    auto mainCompMock = std::make_unique<MainComponentMock>();
    auto filesysMock = std::make_unique<FileSystemMock>();
    IGui* gui = new GuiTester(std::move(mainCompMock), std::move(filesysMock));
    delete gui;
}

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
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(fakeAlbums16));

    EXPECT_CALL(*mainComponentMock, setMusicDirectory(setMusicDir));
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(_, defaultSelectedAlbumIndex));
    EXPECT_CALL(*mainComponentMock, loadMultipleAlbums(_, defaultSelectedAlbumIndex));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(defaultSelectedAlbumIndex));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex));

    gui->setMusicFolder(setMusicDir);
}

TEST_F(GuiTest, WhenRefreshAlbumsIsCalled_ThenGuiCallsSetAlbumsForMusicSetup)
{
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(ReturnRef(fakeAlbums16));

    EXPECT_CALL(*mainComponentMock, setAlbumsForMusicSetup(fakeAlbums16));

    gui->refreshAlbums();
}

TEST_F(GuiTest, WhenSetTimeToPlaySongIsCalled_ThenTheSameIsCalledOnMainComponent)
{
    EXPECT_CALL(*mainComponentMock, setTimeToPlayASong(2000));

    gui->setTimeToPlaySong(2000);
}

TEST_F(GuiTest, WhenSetTimeToSaveInsertedCoinsIsCalled_ThenTheSameIsCalledOnMainComponent)
{
    EXPECT_CALL(*mainComponentMock, setTimeToSaveInsertedCoins(12000));

    gui->setTimeToSaveInsertedCoins(12000);
}

TEST_F(GuiTest, WhenSetPasswordIsCalled_ThenTheSameIsCalledOnMainComponent)
{
    Password password("fakePassword");
    EXPECT_CALL(*mainComponentMock, setPassword(&password));

    gui->setPassword(&password);
}

TEST_F(GuiTest, WhenTurnOffPasswordIsCalled_ThenTheSameIsCalledOnMainComponent)
{
    EXPECT_CALL(*mainComponentMock, turnOffPassword());

    gui->turnOffPassword();
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

TEST_F(GuiTest, WhenShowInsertedAllIsCalled_ThenTheSameIsCalledOnMainComponent)
{
    EXPECT_CALL(*mainComponentMock, showInsertedAll(5));

    gui->showInsertedAll(5);
}

TEST_F(GuiTest, WhenShowInsertedSinceLastSaveIsCalled_ThenTheSameIsCalledOnMainComponent)
{
    EXPECT_CALL(*mainComponentMock, showInsertedSinceLastSave(2));

    gui->showInsertedSinceLastSave(2);
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
