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
    const auto songPath = "fakeSongPath";
    const juce::String userInputNumber1("00101");
    const juce::String userInputNumber2("00102");
    constexpr int defaultSelectedAlbumIndex = 1;
    constexpr int defaultSelectedSongIndex = 0;
    constexpr int defaultAlbumStep = 8;
    const juce::String emptyString = "";

    //apparently the first parameter can be anything as long as the last one is the correct char and the second is zero
    const juce::KeyPress keyC(0, 0, 'c');
    const juce::KeyPress keyH(0, 0, 'h');
    const juce::KeyPress keyA(0, 0, 'a');
    const juce::KeyPress keyS(0, 0, 's');
    const juce::KeyPress keyM(0, 0, 'm');
    const juce::KeyPress keyO(0, 0, 'o');
    const juce::KeyPress keyP(0, 0, 'p');
    const juce::KeyPress keyL(0, 0, 'l');
    const juce::KeyPress keyK(0, 0, 'k');
    const juce::KeyPress keyJ(0, 0, 'j');
    const juce::KeyPress keyQ(0, 0, 'q');
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

TEST_F(GuiTest, WhenMainComponentSendsTimeToPlayASongChangedSignal_ThenGuiSignalizeIt)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::fooInt, gui->timeToPlayASongChangedSignal);

    EXPECT_CALL(fooMock, fooInt(3));

    mainComponentMock->timeToPlayASongChangedSignal(3);
}

// keyPress

TEST_F(GuiTest, WhenMainComponentSendsKeyPressedSignalA_ThenGuiSignalizeIncreaseVolume)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::foo, gui->increaseSoundVolumeSignal);

    EXPECT_CALL(fooMock, foo());

    mainComponentMock->keyPressedSignal(keyA);
}

TEST_F(GuiTest, WhenMainComponentSendsKeyPressedSignalS_ThenGuiSignalizeDecreaseVolume)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::foo, gui->decreaseSoundVolumeSignal);

    EXPECT_CALL(fooMock, foo());

    mainComponentMock->keyPressedSignal(keyS);
}

TEST_F(GuiTest, WhenMainComponentSendsKeyPressedSignalM_ThenGuiSignalizeSwitchMute)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::foo, gui->switchMuteStatusSignal);

    EXPECT_CALL(fooMock, foo());

    mainComponentMock->keyPressedSignal(keyM);
}

TEST_F(GuiTest, WhenMainComponentSendsKeyPressedSignalO_ThenGuiSignalizeCoinInserted50)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::foo, gui->coinInserted50Signal);

    EXPECT_CALL(fooMock, foo());

    mainComponentMock->keyPressedSignal(keyO);
}

TEST_F(GuiTest, WhenMainComponentSendsKeyPressedSignalP_ThenGuiSignalizeCoinInserted100)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::foo, gui->coinInserted100Signal);

    EXPECT_CALL(fooMock, foo());

    mainComponentMock->keyPressedSignal(keyP);
}

TEST_F(GuiTest, WhenMainComponentSendsKeyPressedSignalL_ThenGuiSignalizeCoinInserted200)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::foo, gui->coinInserted200Signal);

    EXPECT_CALL(fooMock, foo());

    mainComponentMock->keyPressedSignal(keyL);
}

TEST_F(GuiTest, WhenMainComponentSendsKeyPressedSignalK_ThenGuiSignalizeCreditIncrease)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::foo, gui->creditIncreaseSignal);

    EXPECT_CALL(fooMock, foo());

    mainComponentMock->keyPressedSignal(keyK);
}

TEST_F(GuiTest, WhenMainComponentSendsKeyPressedSignalJ_ThenGuiSignalizeCreditDecrease)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::foo, gui->creditDecreaseSignal);

    EXPECT_CALL(fooMock, foo());

    mainComponentMock->keyPressedSignal(keyJ);
}

TEST_F(GuiTest, WhenMainComponentSendsKeyPressedSignalQ_ThenGuiSignalizeShutdown)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::foo, gui->shutDownSignal);

    EXPECT_CALL(fooMock, foo());

    mainComponentMock->keyPressedSignal(keyQ);
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

TEST_F(GuiTest, GivenThereIsAlmostEnoughCurrentUserInputToPlayASong_WhenMainComponentSendsKeyPressedNumberAndSongIsExisting_ThenGuiSendsPlaySongSignal)
{
    JuceEventLoopRunner eventLoopRunner;

    const int timeToPlaySong(100);
    EXPECT_CALL(*mainComponentMock, setTimeToPlayASong(_));
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

TEST_F(GuiTest, GivenThereIsSongToPlayOrCancel_WhenMainComponentSendsKeyPressedNumber_ThenItIsIgnored)
{
    const int timeToPlaySong(100);
    EXPECT_CALL(*mainComponentMock, setTimeToPlayASong(_));
    gui->setTimeToPlaySong(timeToPlaySong);
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(_)).Times(5);
    mainComponentMock->keyPressedSignal(keyNumber5);
    mainComponentMock->keyPressedSignal(keyNumber6);
    mainComponentMock->keyPressedSignal(keyNumber7);
    mainComponentMock->keyPressedSignal(keyNumber8);
    ON_CALL(*fileSystemMock, getSongFilePath(_, _, _, _)).WillByDefault(Return("FakeFileName"));
    mainComponentMock->keyPressedSignal(keyNumber9);

    mainComponentMock->keyPressedSignal(keyNumber8);
}

TEST_F(GuiTest, GivenAlmostEnoughCurrentUserInputToPlayASong_WhenMainComponentSendsKeyPressedNumberAndSongIsNotExisting_ThenErrorIsShown)
{
    EXPECT_CALL(*mainComponentMock, setTimeToPlayASong(_));
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
    EXPECT_CALL(*mainComponentMock, setTimeToPlayASong(_));
    gui->setTimeToPlaySong(0);
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(emptyString));

    mainComponentMock->keyPressedSignal(keyDot);
}

TEST_F(GuiTest, GivenThereIsNotEnoughCurrentUserInputToPlayASong_WhenMainComponentSendsKeyPressedSignalDot_ThenCurrentUserInputNumberIsReset)
{
    EXPECT_CALL(*mainComponentMock, setTimeToPlayASong(_));
    gui->setTimeToPlaySong(0);
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(_)).Times(4);
    mainComponentMock->keyPressedSignal(keyNumber1);
    mainComponentMock->keyPressedSignal(keyNumber2);
    mainComponentMock->keyPressedSignal(keyNumber3);
    mainComponentMock->keyPressedSignal(keyNumber4);

    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(emptyString));

    mainComponentMock->keyPressedSignal(keyDot);
}

TEST_F(GuiTest, DISABLED_GivenThereIsEnoughCurrentUserInputToPlayASongAndNoDotPressIsGiven_WhenMainComponentSendsKeyPressedSignalDot_Then)
{
    EXPECT_CALL(*mainComponentMock, setTimeToPlayASong(_));
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

TEST_F(GuiTest, GivenThereIsEnoughCurrentUserInputToPlayASong_WhenMainComponentSendsKeyPressedSignalDotInTimeToCancel_ThenCurrentUserInputNumberIsReset)
{
    JuceEventLoopRunner eventLoopRunner;
    EXPECT_CALL(*mainComponentMock, setTimeToPlayASong(_));
    const int timeToPlay(200);
    gui->setTimeToPlaySong(timeToPlay);
    ON_CALL(*fileSystemMock, getSongFilePath(_, _, _, _)).WillByDefault(Return("FakeFileName"));
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(_)).Times(5);
    mainComponentMock->keyPressedSignal(keyNumber5);
    mainComponentMock->keyPressedSignal(keyNumber6);
    mainComponentMock->keyPressedSignal(keyNumber7);
    mainComponentMock->keyPressedSignal(keyNumber8);
    mainComponentMock->keyPressedSignal(keyNumber9);

    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(emptyString));

    mainComponentMock->keyPressedSignal(keyDot);
    eventLoopRunner.runEventLoop(timeToPlay / 2);
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
