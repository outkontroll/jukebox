#include "gtest/gtest.h"
#include "MainComponentMock.h"
#include "FileSystemMock.h"
#include "GuiTester.h"
#include "Song.h"
#include "FreeFunctions.h"
#include "ResourceId.h"
#include "ResourceString.h"
#include "JuceEventLoopRunner.h"

#include <chrono>
#include <thread>

using namespace jukebox;
using namespace jukebox::gui;
using namespace jukebox::audio;
using namespace testing;

namespace {
    const char* defaultMusicDir = "";
    const auto setMusicDir = "fakeMusicDir";
    const auto songPath = "fakeSongPath";
    const juce::String userInputNumber1("00101");
    const juce::String userInputNumber2("00102");
    constexpr int defaultSelectedAlbumIndex = 1;
    constexpr int defaultSelectedSongIndex = 0;
    constexpr int defaultAlbumStep = 8;
    constexpr unsigned int testCredits = 12;
    const juce::String emptyString = "";

    //apparently the first parameter can be anything as long as the last one is the correct char and the second is zero
    const juce::KeyPress keyC(0, 0, 'c');
    const juce::KeyPress keyH(0, 0, 'h');
    const juce::KeyPress keyDot(0, 0, '.');
    const juce::KeyPress keyMinus(0, 0, '-');
    const juce::KeyPress keyPlus(0, 0, '+');
    const juce::KeyPress keyNumber0(0, 0, '0');
    const juce::KeyPress keyNumber1(0, 0, '1');
    const juce::KeyPress keyNumber2(0, 0, '2');
    const juce::KeyPress keyNumber3(0, 0, '3');
    const juce::KeyPress keyNumber4(0, 0, '4');
    const juce::KeyPress keyNumber5(0, 0, '5');
    const juce::KeyPress keyNumber6(0, 0, '6');
    const juce::KeyPress keyNumber7(0, 0, '7');
    const juce::KeyPress keyNumber8(0, 0, '8');
    const juce::KeyPress keyNumber9(0, 0, '9');
    const juce::KeyPress keyF4(juce::KeyPress::F4Key);
    const juce::KeyPress keyEsc(juce::KeyPress::escapeKey);
    const juce::KeyPress keyBackspace(juce::KeyPress::backspaceKey);
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

// signal subscriptions

TEST_F(GuiTest, WhenMainComponentSendsPlayNextSongSignal_ThenGuiSignalizeIt)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::fooSong, gui->playNextSongSignal);

    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(fooMock, fooSong(song));

    mainComponentMock->playNextSongSignal(song);
}

TEST_F(GuiTest, WhenMainComponentSendsMusicDirectoryChangedSignal_ThenGuiSignalizeIt)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::fooString, gui->musicDirectoryChangedSignal);

    std::string foo("fakeMusicDir");

    EXPECT_CALL(fooMock, fooString(foo));

    mainComponentMock->musicDirectoryChangedSignal(foo);
}

TEST_F(GuiTest, WhenMainComponentSendsKeyPressedSignalH_ThenGuiCallsSwitchBetweenAlbumViews)
{
    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews()).Times(2);

    mainComponentMock->keyPressedSignal(keyH);
    mainComponentMock->keyPressedSignal(keyH);
}

TEST_F(GuiTest, GivenGuiIsInSetupState_WhenMainComponentSendsKeyPressedSignalH_ThenGuiDoesNotSwitch)
{
    EXPECT_CALL(*mainComponentMock, switchBetweenUserModeViews());
    mainComponentMock->keyPressedSignal(keyEsc);

    mainComponentMock->keyPressedSignal(keyH);
}

TEST_F(GuiTest, WhenMainComponentSendsKeyPressedSignalF4_ThenGuiSignalsExitRequested)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::foo, gui->exitRequestedSignal);

    EXPECT_CALL(fooMock, foo());

    mainComponentMock->keyPressedSignal(keyF4);
}

TEST_F(GuiTest, GivenGuiIsInMultipleAlbumsState_WhenMainComponentSendsKeyPressedSignalEsc_ThenGuiCallsSwitchBetweenUserModeViewsAndSignalsUpdateStatistics)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::foo, gui->requestStatisticsSignal);

    EXPECT_CALL(*mainComponentMock, switchBetweenUserModeViews());
    EXPECT_CALL(fooMock, foo());

    mainComponentMock->keyPressedSignal(keyEsc);
}

TEST_F(GuiTest, GivenGuiIsInSingleAlbumState_WhenMainComponentSendsKeyPressedSignalEsc_ThenGuiCallsSwitchBetweenUserModeViewsAndSignalsUpdateStatistics)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::foo, gui->requestStatisticsSignal);
    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());
    mainComponentMock->keyPressedSignal(keyH);

    EXPECT_CALL(*mainComponentMock, switchBetweenUserModeViews());
    EXPECT_CALL(fooMock, foo());

    mainComponentMock->keyPressedSignal(keyEsc);
}

TEST_F(GuiTest, GivenGuiWasInMultipleAlbumsStateAndIsInSetupState_WhenMainComponentSendsKeyPressedSignalEsc_ThenGuiSwitchBackToMultipleAlbumsState)
{
    EXPECT_CALL(*mainComponentMock, switchBetweenUserModeViews());
    mainComponentMock->keyPressedSignal(keyEsc);

    EXPECT_CALL(*mainComponentMock, switchBetweenUserModeViews());
    mainComponentMock->keyPressedSignal(keyEsc);
}

TEST_F(GuiTest, GivenGuiWasInSingleAlbumStateAndIsInSetupState_WhenMainComponentSendsKeyPressedSignalEsc_ThenGuiSwitchBackToSingleAlbumState)
{
    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());
    mainComponentMock->keyPressedSignal(keyH);
    EXPECT_CALL(*mainComponentMock, switchBetweenUserModeViews());
    mainComponentMock->keyPressedSignal(keyEsc);

    EXPECT_CALL(*mainComponentMock, switchBetweenUserModeViews());
    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());
    mainComponentMock->keyPressedSignal(keyEsc);
}

TEST_F(GuiTest, WhenMainComponentSendsKeyPressedSignalBackspace_ThenGuiSignalsRemovePlayedSong)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::foo, gui->removePlayedSongSignal);

    EXPECT_CALL(fooMock, foo());

    mainComponentMock->keyPressedSignal(keyBackspace);
}

TEST_F(GuiTest, GivenGuiIsInMultipleAlbumsState_WhenMainComponentSendsKeyPressedSignalC_ThenGuiCallsLoadSimpleAlbumAndUpdateAlbumAndSongSelection)
{
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(defaultMusicDir, defaultSelectedAlbumIndex + 1, _));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(defaultSelectedAlbumIndex + 1));
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(defaultMusicDir, defaultSelectedAlbumIndex + 2, _));
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

    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(defaultMusicDir, defaultSelectedAlbumIndex + 1, _));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(defaultSelectedAlbumIndex + 1));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex));

    mainComponentMock->keyPressedSignal(keyC);
}

TEST_F(GuiTest, GivenThereIsAlmostEnoughCurrentUserInputToPlayASong_WhenMainComponentSendsKeyPressedNumberAndTheSongIsExisting_ThenGuiSendsPlaySongSignal)
{
    JuceEventLoopRunner eventLoopRunner;

    const int timeToPlaySong(100);
    gui->setTimeToPlaySong(timeToPlaySong);
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(_)).Times(4);
    mainComponentMock->keyPressedSignal(keyNumber5);
    mainComponentMock->keyPressedSignal(keyNumber6);
    mainComponentMock->keyPressedSignal(keyNumber7);
    mainComponentMock->keyPressedSignal(keyNumber8);

    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(_));
    ON_CALL(*fileSystemMock, getSongFilePath(_, _, _, _)).WillByDefault(Return("FakeFileName"));

    Song song{567, 89, "FakeFileName", "fakeVisibleName"};
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::fooSong, gui->playSongSignal);
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(emptyString));
    EXPECT_CALL(fooMock, fooSong(song));

    mainComponentMock->keyPressedSignal(keyNumber9);
    eventLoopRunner.runEventLoop(timeToPlaySong);
}

TEST_F(GuiTest, GivenAlmostEnoughCurrentUserInputToPlayASong_WhenMainComponentSendsFifthKeyPressedNumberAndSongIsNotExisting_ThenErrorIsShown)
{
    gui->setTimeToPlaySong(5000);
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(_)).Times(4);
    mainComponentMock->keyPressedSignal(keyNumber5);
    mainComponentMock->keyPressedSignal(keyNumber6);
    mainComponentMock->keyPressedSignal(keyNumber7);
    mainComponentMock->keyPressedSignal(keyNumber8);

    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(_));
    const juce::String errorSongNotExists(Resources::getResourceStringFromId(ResourceId::ErrorSongNotExists));
    EXPECT_CALL(*mainComponentMock, showStatusMessage(errorSongNotExists));
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(emptyString));

    mainComponentMock->keyPressedSignal(keyNumber9);
}

TEST_F(GuiTest, GivenThereIsNoCurrentUserInput_WhenMainComponentSendsKeyPressedSignalDot_ThenCurrentUserInputNumberIsReset)
{
    gui->setTimeToPlaySong(0);
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(emptyString));

    mainComponentMock->keyPressedSignal(keyDot);
}

TEST_F(GuiTest, GivenThereIsNotEnoughCurrentUserInputToPlayASong_WhenMainComponentSendsKeyPressedSignalDot_ThenCurrentUserInputNumberIsReset)
{
    gui->setTimeToPlaySong(0);
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(_)).Times(4);
    mainComponentMock->keyPressedSignal(keyNumber1);
    mainComponentMock->keyPressedSignal(keyNumber2);
    mainComponentMock->keyPressedSignal(keyNumber3);
    mainComponentMock->keyPressedSignal(keyNumber4);

    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(emptyString));

    mainComponentMock->keyPressedSignal(keyDot);
}

TEST_F(GuiTest, DISABLED_Signaling)
{
    gui->setTimeToPlaySong(100);
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(_)).Times(5);
    mainComponentMock->keyPressedSignal(keyNumber5);
    mainComponentMock->keyPressedSignal(keyNumber6);
    mainComponentMock->keyPressedSignal(keyNumber7);
    mainComponentMock->keyPressedSignal(keyNumber8);
    ON_CALL(*fileSystemMock, getSongFilePath(_, _, _, _)).WillByDefault(Return(songPath));

    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::fooSong, gui->playSongSignal);

    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(fooMock, fooSong(song));

    mainComponentMock->keyPressedSignal(keyNumber9);

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);

}

TEST_F(GuiTest, DISABLED_GivenThereIsEnoughCurrentUserInputToPlayASongAndNoDotPressIsGiven_WhenMainComponentSendsKeyPressedSignalDot_Then)
{
    gui->setTimeToPlaySong(0);
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(_)).Times(5);
    mainComponentMock->keyPressedSignal(keyNumber5);
    mainComponentMock->keyPressedSignal(keyNumber6);
    mainComponentMock->keyPressedSignal(keyNumber7);
    mainComponentMock->keyPressedSignal(keyNumber8);
    mainComponentMock->keyPressedSignal(keyNumber9);

    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(emptyString)).Times(0);

    //TODO sign up for signal

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);

    mainComponentMock->keyPressedSignal(keyDot);
}

TEST_F(GuiTest, DISABLED_GivenThereIsEnoughCurrentUserInputToPlayASong_WhenMainComponentSendsKeyPressedSignalDotInTimeToCancel_ThenCurrentUserInputNumberIsReset)
{
    gui->setTimeToPlaySong(5000);
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(_)).Times(5);
    mainComponentMock->keyPressedSignal(keyNumber5);
    mainComponentMock->keyPressedSignal(keyNumber6);
    mainComponentMock->keyPressedSignal(keyNumber7);
    mainComponentMock->keyPressedSignal(keyNumber8);
    mainComponentMock->keyPressedSignal(keyNumber9);

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);

    //TODO set expectations

    mainComponentMock->keyPressedSignal(keyDot);
}

//TODO this test is incomplete because when the timer expires there will be additional (currently untested) calls too
TEST_F(GuiTest, GivenGuiIsInSingleAlbumsStateAndThereIsNoSongSelectedToPlay_WhenMainComponentSendsKeyPressedSignalDot_ThenTheFirstSongWillBePlayed)
{
    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());
    mainComponentMock->keyPressedSignal(keyH);

    ON_CALL(*fileSystemMock, getSongFilePath(_, _, _, _)).WillByDefault(Return(songPath));
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(userInputNumber1));

    mainComponentMock->keyPressedSignal(keyDot);
}

//TODO this test is incomplete because when the timer expires there will be additional (currently untested) calls too
TEST_F(GuiTest, GivenGuiIsInSingleAlbumsStateAndThereIsNoSongSelectedToPlayAndTheCurrentSongIsNotTheFirstOne_WhenMainComponentSendsKeyPressedSignalDot_ThenTheCurrentSelectedSongWillBePlayed)
{
    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());
    mainComponentMock->keyPressedSignal(keyH);
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex + 1));
    mainComponentMock->keyPressedSignal(keyC);

    ON_CALL(*fileSystemMock, getSongFilePath(_, _, _, _)).WillByDefault(Return(songPath));
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(userInputNumber2));

    mainComponentMock->keyPressedSignal(keyDot);
}

TEST_F(GuiTest, GivenGuiIsInMultipleAlbumsStateAndNotOnEndOfRange_WhenMainComponentSendsKeyPressedSignalMinus_ThenGuiLoadsTheNextSetOfAlbums)
{
    const int expectedIndex = defaultSelectedAlbumIndex + defaultAlbumStep;
    EXPECT_CALL(*mainComponentMock, loadMultipleAlbums(defaultMusicDir, expectedIndex, _));
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(defaultMusicDir, expectedIndex, _));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex));

    mainComponentMock->keyPressedSignal(keyMinus);
}

TEST_F(GuiTest, GivenGuiIsInMultipleAlbumsStateAndNotAtTheEndOfRange_WhenMainComponentSendsKeyPressedSignalPlus_ThenGuiLoadsThePreviousSetOfAlbums)
{
    //this block is needed as setup because we are at the begin so underflow would occur
    EXPECT_CALL(*mainComponentMock, loadMultipleAlbums(_, _, _));
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(_, _, _));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(_));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(_));
    mainComponentMock->keyPressedSignal(keyMinus);

    const int expectedIndex = defaultSelectedAlbumIndex;
    EXPECT_CALL(*mainComponentMock, loadMultipleAlbums(defaultMusicDir, expectedIndex, _));
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(defaultMusicDir, expectedIndex, _));
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
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(defaultMusicDir, expectedIndex, _));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex));

    mainComponentMock->keyPressedSignal(keyMinus);
}

TEST_F(GuiTest, GuiIsInSingleAlbumStateAndNotOnEndOfRange_WhenMainComponentSendsKeyPressedSignalPlus_ThenGuiLoadsThePreviousAlbum)
{
    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());
    mainComponentMock->keyPressedSignal(keyH);
    //this block is needed as setup because we are at the begin so underflow would occur
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(_, _, _));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(_));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(_));
    mainComponentMock->keyPressedSignal(keyMinus);

    const int expectedIndex = defaultSelectedAlbumIndex;
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(defaultMusicDir, expectedIndex, _));
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
