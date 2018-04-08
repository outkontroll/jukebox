#include "gtest/gtest.h"
#include "MainComponentMock.h"
#include "GuiTester.h"
#include "Song.h"
#include "FreeFunctions.h"
#include "ResourceId.h"

using namespace jukebox;
using namespace jukebox::gui;
using namespace jukebox::audio;
using namespace testing;

namespace {
    const char* defaultMusicDir = "";
    const auto setMusicDir = "fakeMusicDir";
    constexpr int defaultSelectedAlbumIndex = 1;
    constexpr int defaultSelectedSongIndex = 0;
    constexpr int defaultAlbumStep = 8;
    constexpr unsigned int testCredits = 12;
    const juce::String emptyString = "";
    const juce::String TranslatedStringPlaying = "Playing";

    //apparently the first parameter can be anything as long as the last one is the correct char and the second is zero
    const juce::KeyPress keyC(0, 0, 'c');
    const juce::KeyPress keyH(0, 0, 'h');
    const juce::KeyPress keyDot(0, 0, '.');
    const juce::KeyPress keyMinus(0, 0, '-');
    const juce::KeyPress keyPlus(0, 0, '+');
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

// signal subscriptions

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
    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews()).Times(2);

    mainComponentMock->keyPressedSignal(keyH);
    mainComponentMock->keyPressedSignal(keyH);
}

TEST_F(GuiTest, GivenGuiIsInMultipleAlbumsState_WhenMainComponentSendsKeyPressedSignalC_ThenGuiCallsLoadSimpleAlbumAndUpdateAlbumAndSongSelection)
{
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(defaultMusicDir, defaultSelectedAlbumIndex + 1));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(defaultSelectedAlbumIndex + 1));
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(defaultMusicDir, defaultSelectedAlbumIndex + 2));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(defaultSelectedAlbumIndex + 2));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex)).Times(2);

    mainComponentMock->keyPressedSignal(keyC);
    mainComponentMock->keyPressedSignal(keyC);
}

TEST_F(GuiTest, GivenGuiIsInSingleAlbumsState_WhenMainComponentSendsKeyPressedSignalC_ThenGuiCallsUpdateSongSelection)
{
    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());
    mainComponentMock->keyPressedSignal(keyH);

    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex + 1));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex + 2));

    mainComponentMock->keyPressedSignal(keyC);
    mainComponentMock->keyPressedSignal(keyC);
}

TEST_F(GuiTest, GivenGuiIsInMultipleAlbumsStateAndSongSelectionIsDifferent_WhenMainComponentSendsKeyPressedSignalC_ThenGuiCallsLoadSimpleAlbumAndUpdateAlbumAndSongSelection)
{
    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());
    mainComponentMock->keyPressedSignal(keyH);
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex + 1));
    mainComponentMock->keyPressedSignal(keyC);
    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());
    mainComponentMock->keyPressedSignal(keyH);

    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(defaultMusicDir, defaultSelectedAlbumIndex + 1));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(defaultSelectedAlbumIndex + 1));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex));

    mainComponentMock->keyPressedSignal(keyC);
}

TEST_F(GuiTest, GivenThereIsNoSongSelectedToPlay_WhenMainComponentSendsKeyPressedSignalDot_ThenCurrentUserInputNumberIsReset)
{
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(emptyString));

    mainComponentMock->keyPressedSignal(keyDot);
}

TEST_F(GuiTest, GivenGuiIsInMultipleAlbumsStateAndNotOnEndOfRange_WhenMainComponentSendsKeyPressedSignalMinus_ThenGuiLoadsTheNextSetOfAlbums)
{
    const int expectedIndex = defaultSelectedAlbumIndex + defaultAlbumStep;
    EXPECT_CALL(*mainComponentMock, loadMultipleAlbums(defaultMusicDir, expectedIndex));
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(defaultMusicDir, expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex));

    mainComponentMock->keyPressedSignal(keyMinus);
}

TEST_F(GuiTest, GivenGuiIsInMultipleAlbumsStateAndNotAtTheEndOfRange_WhenMainComponentSendsKeyPressedSignalPlus_ThenGuiLoadsThePreviousSetOfAlbums)
{
    //this block is needed as setup because we are at the begin so underflow would occur
    EXPECT_CALL(*mainComponentMock, loadMultipleAlbums(_, _));
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(_, _));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(_));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(_));
    mainComponentMock->keyPressedSignal(keyMinus);

    const int expectedIndex = defaultSelectedAlbumIndex;
    EXPECT_CALL(*mainComponentMock, loadMultipleAlbums(defaultMusicDir, expectedIndex));
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(defaultMusicDir, expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex));

    mainComponentMock->keyPressedSignal(keyPlus);
}

//TODO test range edges

//TODO test overflow, underflow

TEST_F(GuiTest, GuiIsInSingleAlbumStateAndNotOnEndOfRange_WhenMainComponentSendsKeyPressedSignalMinus_ThenGuiLoadsTheNextAlbum)
{
    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());
    mainComponentMock->keyPressedSignal(keyH);

    const int expectedIndex = defaultSelectedAlbumIndex + 1;
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(defaultMusicDir, expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex));

    mainComponentMock->keyPressedSignal(keyMinus);
}

TEST_F(GuiTest, GuiIsInSingleAlbumStateAndNotOnEndOfRange_WhenMainComponentSendsKeyPressedSignalPlus_ThenGuiLoadsThePreviousAlbum)
{
    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());
    mainComponentMock->keyPressedSignal(keyH);
    //this block is needed as setup because we are at the begin so underflow would occur
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(_, _));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(_));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(_));
    mainComponentMock->keyPressedSignal(keyMinus);

    const int expectedIndex = defaultSelectedAlbumIndex;
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(defaultMusicDir, expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex));

    mainComponentMock->keyPressedSignal(keyPlus);
}

//TODO test range edges

//TODO test overflow, underflow

// public interface

TEST_F(GuiTest, WhenRefreshCreditsCalled_ThenSameIsCalledOnMainComponentWithSameParameter)
{
    EXPECT_CALL(*mainComponentMock, refreshCredits(testCredits));

    gui->refreshCredits(testCredits);
}

TEST_F(GuiTest, WhenShowStatusMessageIsCalledWithResourceId_ThenTheSameIsCalledOnMainComponentWithTranslatedString)
{
    EXPECT_CALL(*mainComponentMock, showStatusMessage(TranslatedStringPlaying));

    gui->showStatusMessage(ResourceId::Playing);
}

TEST_F(GuiTest, WhenSetMusicFolderIsCalled_ThenGuiCallsLoadSingleAndMultipleAlbumsAndUpdateSelection)
{
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(setMusicDir, defaultSelectedAlbumIndex));
    EXPECT_CALL(*mainComponentMock, loadMultipleAlbums(setMusicDir, defaultSelectedAlbumIndex));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(defaultSelectedAlbumIndex));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex));

    gui->setMusicFolder(setMusicDir);
}

TEST_F(GuiTest, WhenSetCurrentlyPlayedSongIsCalled_ThenTheSameAndStatusUpdateIsCalledOnMainComponent)
{
    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*mainComponentMock, setCurrentlyPlayedSong(song));
    EXPECT_CALL(*mainComponentMock, showStatusMessage(TranslatedStringPlaying));

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

TEST_F(GuiTest, WhenPrepareForExitIsCalled_ThenTheSameIsCalledOnMainComponent)
{
    EXPECT_CALL(*mainComponentMock, prepareForExit());

    gui->prepareForExit();
}
