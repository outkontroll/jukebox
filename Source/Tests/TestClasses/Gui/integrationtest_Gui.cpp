#include "gtest/gtest.h"
#include "MainComponentMock.h"
#include "GuiTester.h"
#include "Song.h"
#include "FreeFunctions.h"

using namespace jukebox::gui;
using namespace jukebox::audio;
using namespace testing;

namespace {
    const std::string defaultMusicDir = "";
    const auto setMusicDir = "fakeMusicDir";
    constexpr int defaultSelectedAlbumIndex = 1;
    juce::KeyPress keyC(99, 0, 'c');
    juce::KeyPress keyH(104, 0, 'h');
}

class GuiTest : public ::testing::Test
{    
protected:
    void SetUp() override
    {
        auto mainCompMock = std::make_unique<StrictMock<MainComponentMock>>();
        mainComponentMock = mainCompMock.get();
        gui = std::make_unique<GuiTester>(std::move(mainCompMock));
    }

    std::unique_ptr<GuiTester> gui;
    StrictMock<MainComponentMock>* mainComponentMock;

    jukebox::signals::Slot eventsSlot;
};

TEST_F(GuiTest, WhenMainComponentSendsPlayNextSongSignal_ThenGuiSignalizeIt)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::fooSong, gui->playNextSongSignal);

    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(fooMock, fooSong(song));

    mainComponentMock->playNextSongSignal(song);
}

TEST_F(GuiTest, WhenMainComponentSendsKeyPressedSignalH_ThenGuiCallsSwitchBetweenAlbumViews)
{
    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());

    mainComponentMock->keyPressedSignal(keyH);
}

TEST_F(GuiTest, GivenGuiIsInDefaultState_WhenMainComponentSendsKeyPressedSignalC_ThenGuiCallsLoadSimpleAlbumAndUpdateSelection)
{
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(defaultMusicDir, defaultSelectedAlbumIndex + 1));
    EXPECT_CALL(*mainComponentMock, updateSelection(defaultSelectedAlbumIndex + 1));

    mainComponentMock->keyPressedSignal(keyC);
}

TEST_F(GuiTest, GivenGuiIsInMultipleAlbumsState_WhenMainComponentSendsKeyPressedSignalC_ThenGuiCallsLoadSimpleAlbumAndUpdateSelection)
{
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(defaultMusicDir, defaultSelectedAlbumIndex + 1));
    EXPECT_CALL(*mainComponentMock, updateSelection(defaultSelectedAlbumIndex + 1));
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(defaultMusicDir, defaultSelectedAlbumIndex + 2));
    EXPECT_CALL(*mainComponentMock, updateSelection(defaultSelectedAlbumIndex + 2));

    mainComponentMock->keyPressedSignal(keyC);
    mainComponentMock->keyPressedSignal(keyC);
}

TEST_F(GuiTest, WhenSetMusicFolderIsCalled_ThenGuiCallsLoadSingleAndMultipleAlbumsAndUpdateSelection)
{
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(setMusicDir, defaultSelectedAlbumIndex));
    EXPECT_CALL(*mainComponentMock, loadMultipleAlbums(setMusicDir, defaultSelectedAlbumIndex));
    EXPECT_CALL(*mainComponentMock, updateSelection(defaultSelectedAlbumIndex));

    gui->setMusicFolder(setMusicDir);
}
