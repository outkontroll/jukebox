#include "GuiTester.h"
#include "Song.h"
#include "FreeFunctions.h"
#include "ResourceId.h"
#include "ResourceString.h"
#include "JuceEventLoopRunner.h"
#include "Password.h"

#include <chrono>
#include <thread>

using namespace jukebox;
using namespace jukebox::gui;
using namespace jukebox::audio;
using namespace testing;

namespace {
    const juce::String userInputNumber1("00101");
    const juce::String userInputNumber2("00102");
    constexpr int defaultSelectedAlbumIndex = 1;
    constexpr int defaultSelectedSongIndex = 0;
    constexpr int defaultAlbumStep = 8;
    const juce::String emptyString = "";
    const std::vector<AlbumInfo> singleElementAlbum{{}};
    const Song song1{1, 1, "FakeFileName", "fakeVisibleName"};
    const Song song2{1, 2, "FakeFileName", "fakeVisibleName"};
    const Song song3{1, 3, "FakeFileName", "fakeVisibleName"};
    const std::vector<AlbumInfo> fakeAlbums16(16, {{song1, song2, song3}, "", "", "", 1});
    const std::vector<AlbumInfo> fakeAlbumsEmptySongs(1, {{}, "", "", "", 1});

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

// signal subscriptions

TEST_F(GuiTest, WhenMainComponentSendsPlayNextSongSignal_ThenGuiSignalizeIt)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::fooSong, gui->playNextSongSignal);

    EXPECT_CALL(fooMock, fooSong(song1));

    mainComponentMock->playNextSongSignal(song1);
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

TEST_F(GuiTest, WhenMainComponentSendsTimeToSaveInsertedCoinsChangedSignal_ThenGuiSignalizeIt)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::fooInt, gui->timeToSaveInsertedCoinsChangedSignal);

    EXPECT_CALL(fooMock, fooInt(3));

    mainComponentMock->timeToSaveInsertedCoinsChangedSignal(3);
}

TEST_F(GuiTest, WhenMainComponentSendsPasswordChangedSignal_ThenGuiSignalizeIt)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::fooPassword, gui->passwordChangedSignal);

    Password password{"fakePassword"};
    EXPECT_CALL(fooMock, fooPassword(password));

    mainComponentMock->passwordChangedSignal(password);
}

TEST_F(GuiTest, WhenMainComponentSendsTurnOffPasswordSignal_ThenGuiSignalizeIt)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::foo, gui->passwordTurnedOffSignal);

    EXPECT_CALL(fooMock, foo());

    mainComponentMock->passwordTurnedOffSignal();
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

TEST_F(GuiTest, GivenGuiIsInSetupState_WhenMainComponentSendsKeyPressedSignalH_ThenGuiCallSwitchBetweenAdministratorViews)
{
    EXPECT_CALL(*mainComponentMock, switchBetweenUserModes());
    EXPECT_CALL(*mainComponentMock, switchBetweenAdministratorViews());
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

TEST_F(GuiTest, GivenPasswordIsSetAndMainComponentTellsGoodPassword_WhenMainComponentSendsKeyPressedSignalEsc_ThenGuiSwitchesUserMode)
{
    Password password("fakePassword");
    gui->setPassword(password);
    EXPECT_CALL(*mainComponentMock, showPasswordQuestion(password)).WillOnce(Return(true));
    EXPECT_CALL(*mainComponentMock, switchBetweenUserModes());
    mainComponentMock->keyPressedSignal(keyEsc);
}

TEST_F(GuiTest, GivenPasswordIsSetAndMainComponentTellsWrongPassword_WhenMainComponentSendsKeyPressedSignalEsc_ThenGuiStaysInSameUserModeAndShowsError)
{
    Password password("fakePassword");
    gui->setPassword(password);

    EXPECT_CALL(*mainComponentMock, showPasswordQuestion(password)).WillOnce(Return(false));
    const juce::String errorWrongPassword(Resources::getResourceStringFromId(ResourceId::ErrorWrongPassword));
    EXPECT_CALL(*mainComponentMock, showStatusMessage(errorWrongPassword));
    mainComponentMock->keyPressedSignal(keyEsc);
}

TEST_F(GuiTest, GivenPasswordIsSetThenTurnedOff_WhenMainComponentSendsKeyPressedSignalEsc_ThenGuiSwitchesUserMode)
{
    Password password("fakePassword");
    gui->setPassword(password);
    gui->turnOffPassword();
    EXPECT_CALL(*mainComponentMock, switchBetweenUserModes());
    mainComponentMock->keyPressedSignal(keyEsc);
}

TEST_F(GuiTest, GivenGuiIsInMultipleAlbumsState_WhenMainComponentSendsKeyPressedSignalEsc_ThenGuiCallsSwitchBetweenUserModeViewsAndSignalsUpdateStatistics)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::foo, gui->requestStatisticsSignal);

    EXPECT_CALL(*mainComponentMock, switchBetweenUserModes());
    EXPECT_CALL(fooMock, foo());

    mainComponentMock->keyPressedSignal(keyEsc);
}

TEST_F(GuiTest, GivenGuiIsInSingleAlbumState_WhenMainComponentSendsKeyPressedSignalEsc_ThenGuiCallsSwitchBetweenUserModeViewsAndSignalsUpdateStatistics)
{
    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::foo, gui->requestStatisticsSignal);
    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());
    mainComponentMock->keyPressedSignal(keyH);

    EXPECT_CALL(*mainComponentMock, switchBetweenUserModes());
    EXPECT_CALL(fooMock, foo());

    mainComponentMock->keyPressedSignal(keyEsc);
}

TEST_F(GuiTest, GivenGuiWasInMultipleAlbumsStateAndIsInSetupState_WhenMainComponentSendsKeyPressedSignalEsc_ThenGuiSwitchBackToMultipleAlbumsState)
{
    EXPECT_CALL(*mainComponentMock, switchBetweenUserModes());
    mainComponentMock->keyPressedSignal(keyEsc);

    EXPECT_CALL(*mainComponentMock, switchBetweenUserModes());
    mainComponentMock->keyPressedSignal(keyEsc);
}

TEST_F(GuiTest, GivenGuiWasInSingleAlbumStateAndIsInSetupState_WhenMainComponentSendsKeyPressedSignalEsc_ThenGuiSwitchBackToSingleAlbumState)
{
    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());
    mainComponentMock->keyPressedSignal(keyH);
    EXPECT_CALL(*mainComponentMock, switchBetweenUserModes());
    mainComponentMock->keyPressedSignal(keyEsc);

    EXPECT_CALL(*mainComponentMock, switchBetweenUserModes());
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
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(fakeAlbums16));

    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(_, defaultSelectedAlbumIndex + 1));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(defaultSelectedAlbumIndex + 1));
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(_, defaultSelectedAlbumIndex + 2));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(defaultSelectedAlbumIndex + 2));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex)).Times(2);

    mainComponentMock->keyPressedSignal(keyC);
    mainComponentMock->keyPressedSignal(keyC);
}

TEST_F(GuiTest, GivenGuiIsInSingleAlbumsState_WhenMainComponentSendsKeyPressedSignalC_ThenGuiCallsUpdateSongSelection)
{
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(fakeAlbums16));

    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());
    mainComponentMock->keyPressedSignal(keyH);

    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex + 1));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex + 2));

    mainComponentMock->keyPressedSignal(keyC);
    mainComponentMock->keyPressedSignal(keyC);
}

TEST_F(GuiTest, GivenGuiIsInMultipleAlbumsStateAndSongSelectionIsDifferent_WhenMainComponentSendsKeyPressedSignalC_ThenGuiCallsLoadSimpleAlbumAndUpdateAlbumAndSongSelection)
{
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(fakeAlbums16));

    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());
    mainComponentMock->keyPressedSignal(keyH);
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex + 1));
    mainComponentMock->keyPressedSignal(keyC);
    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());
    mainComponentMock->keyPressedSignal(keyH);

    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(_, defaultSelectedAlbumIndex + 1));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(defaultSelectedAlbumIndex + 1));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex));

    mainComponentMock->keyPressedSignal(keyC);
}

TEST_F(GuiTest, GivenThereIsAlmostEnoughCurrentUserInputToPlayASong_WhenMainComponentSendsKeyPressedNumberAndSongIsExisting_ThenGuiSendsPlaySongSignal)
{
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(fakeAlbums16));

    JuceEventLoopRunner eventLoopRunner;

    const int timeToPlaySong(100);
    EXPECT_CALL(*mainComponentMock, setTimeToPlayASong(_));
    gui->setTimeToPlaySong(timeToPlaySong);
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(_)).Times(4);
    mainComponentMock->keyPressedSignal(keyNumber0);
    mainComponentMock->keyPressedSignal(keyNumber0);
    mainComponentMock->keyPressedSignal(keyNumber1);
    mainComponentMock->keyPressedSignal(keyNumber0);

    juce::String songName("00101");
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(songName));

    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::fooSong, gui->playSongSignal);
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(emptyString));
    EXPECT_CALL(fooMock, fooSong(song1));

    mainComponentMock->keyPressedSignal(keyNumber1);
    eventLoopRunner.runEventLoop(timeToPlaySong);
}

TEST_F(GuiTest, GivenThereIsSongToPlayOrCancel_WhenMainComponentSendsKeyPressedNumber_ThenItIsIgnored)
{
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(fakeAlbums16));

    const int timeToPlaySong(100);
    EXPECT_CALL(*mainComponentMock, setTimeToPlayASong(_));
    gui->setTimeToPlaySong(timeToPlaySong);
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(_)).Times(5);
    mainComponentMock->keyPressedSignal(keyNumber0);
    mainComponentMock->keyPressedSignal(keyNumber0);
    mainComponentMock->keyPressedSignal(keyNumber1);
    mainComponentMock->keyPressedSignal(keyNumber0);
    mainComponentMock->keyPressedSignal(keyNumber1);

    mainComponentMock->keyPressedSignal(keyNumber8);
}

TEST_F(GuiTest, GivenAlmostEnoughCurrentUserInputToPlayASong_WhenMainComponentSendsKeyPressedNumberAndSongIsNotExisting_ThenErrorIsShown)
{
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(fakeAlbums16));

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

TEST_F(GuiTest, GivenThereIsAlmostEnoughCurrentUserInputToPlayAnAlbum_WhenMainComponentSendsKeyPressedNumber0AndAlbumIsExisting_ThenGuiSendsPlaySongSignal)
{
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(fakeAlbums16));
    JuceEventLoopRunner eventLoopRunner;

    const int timeToPlaySong(100);
    EXPECT_CALL(*mainComponentMock, setTimeToPlayASong(_));
    gui->setTimeToPlaySong(timeToPlaySong);
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(_)).Times(4);
    mainComponentMock->keyPressedSignal(keyNumber0);
    mainComponentMock->keyPressedSignal(keyNumber0);
    mainComponentMock->keyPressedSignal(keyNumber1);
    mainComponentMock->keyPressedSignal(keyNumber0);

    juce::String albumName("00100");
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(albumName));

    /*StrictMock<*/FooMock/*>*/ fooMock;
    eventsSlot.connect(&fooMock, &FooMock::fooAlbum, gui->playAlbumSignal);
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(emptyString));
    Album album{1, "001"};
    std::vector<Song> songs{song1, song2, song3};
    EXPECT_CALL(fooMock, fooAlbum(album, songs));

    mainComponentMock->keyPressedSignal(keyNumber0);
    eventLoopRunner.runEventLoop(timeToPlaySong);
}

TEST_F(GuiTest, GivenThereIsAlbumToPlayOrCancel_WhenMainComponentSendsKeyPressedNumber_ThenItIsIgnored)
{
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(fakeAlbums16));

    const int timeToPlaySong(100);
    EXPECT_CALL(*mainComponentMock, setTimeToPlayASong(_));
    gui->setTimeToPlaySong(timeToPlaySong);
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(_)).Times(5);
    mainComponentMock->keyPressedSignal(keyNumber0);
    mainComponentMock->keyPressedSignal(keyNumber0);
    mainComponentMock->keyPressedSignal(keyNumber1);
    mainComponentMock->keyPressedSignal(keyNumber0);

    mainComponentMock->keyPressedSignal(keyNumber0);

    mainComponentMock->keyPressedSignal(keyNumber8);
}

TEST_F(GuiTest, GivenAlmostEnoughCurrentUserInputToPlayAnAlbum_WhenMainComponentSendsKeyPressedNumber0AndAlbumIsNotExisting_ThenErrorIsShown)
{
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(fakeAlbums16));

    EXPECT_CALL(*mainComponentMock, setTimeToPlayASong(_));
    gui->setTimeToPlaySong(5000);
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(_)).Times(4);
    mainComponentMock->keyPressedSignal(keyNumber5);
    mainComponentMock->keyPressedSignal(keyNumber6);
    mainComponentMock->keyPressedSignal(keyNumber7);
    mainComponentMock->keyPressedSignal(keyNumber0);

    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(_));
    const juce::String errorDuringAlbumPlaying(Resources::getResourceStringFromId(ResourceId::ErrorDuringAlbumPlaying));
    EXPECT_CALL(*mainComponentMock, showStatusMessage(errorDuringAlbumPlaying));
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(emptyString));

    mainComponentMock->keyPressedSignal(keyNumber0);
}

TEST_F(GuiTest, GivenAlmostEnoughCurrentUserInputToPlayAnAlbum_WhenMainComponentSendsKeyPressedNumber0AndAlbumIsEmpty_ThenErrorIsShown)
{
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(fakeAlbumsEmptySongs));

    EXPECT_CALL(*mainComponentMock, setTimeToPlayASong(_));
    gui->setTimeToPlaySong(5000);
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(_)).Times(4);
    mainComponentMock->keyPressedSignal(keyNumber0);
    mainComponentMock->keyPressedSignal(keyNumber0);
    mainComponentMock->keyPressedSignal(keyNumber1);
    mainComponentMock->keyPressedSignal(keyNumber0);

    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(_));
    const juce::String errorDuringAlbumPlaying(Resources::getResourceStringFromId(ResourceId::ErrorDuringAlbumPlaying));
    EXPECT_CALL(*mainComponentMock, showStatusMessage(errorDuringAlbumPlaying));
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(emptyString));

    mainComponentMock->keyPressedSignal(keyNumber0);
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

TEST_F(GuiTest, GivenThereIsEnoughCurrentUserInputToPlayASong_WhenMainComponentSendsKeyPressedSignalDotInTimeToCancel_ThenCurrentUserInputNumberIsReset)
{
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(fakeAlbums16));

    JuceEventLoopRunner eventLoopRunner;
    EXPECT_CALL(*mainComponentMock, setTimeToPlayASong(_));
    const int timeToPlay(200);
    gui->setTimeToPlaySong(timeToPlay);
    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(_)).Times(5);
    mainComponentMock->keyPressedSignal(keyNumber0);
    mainComponentMock->keyPressedSignal(keyNumber0);
    mainComponentMock->keyPressedSignal(keyNumber1);
    mainComponentMock->keyPressedSignal(keyNumber0);
    mainComponentMock->keyPressedSignal(keyNumber1);

    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(emptyString));

    mainComponentMock->keyPressedSignal(keyDot);
    eventLoopRunner.runEventLoop(timeToPlay / 2);
}

//TODO this test is incomplete because when the timer expires there will be additional (currently untested) calls too
TEST_F(GuiTest, GivenGuiIsInSingleAlbumsStateAndThereIsNoSongSelectedToPlay_WhenMainComponentSendsKeyPressedSignalDot_ThenTheFirstSongWillBePlayed)
{
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(fakeAlbums16));

    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());
    mainComponentMock->keyPressedSignal(keyH);

    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(userInputNumber1));

    mainComponentMock->keyPressedSignal(keyDot);
}

//TODO this test is incomplete because when the timer expires there will be additional (currently untested) calls too
TEST_F(GuiTest, GivenGuiIsInSingleAlbumsStateAndThereIsNoSongSelectedToPlayAndTheCurrentSongIsNotTheFirstOne_WhenMainComponentSendsKeyPressedSignalDot_ThenTheCurrentSelectedSongWillBePlayed)
{
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(fakeAlbums16));

    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());
    mainComponentMock->keyPressedSignal(keyH);
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex + 1));
    mainComponentMock->keyPressedSignal(keyC);

    EXPECT_CALL(*mainComponentMock, setCurrentUserInputNumber(userInputNumber2));

    mainComponentMock->keyPressedSignal(keyDot);
}

TEST_F(GuiTest, GivenGuiIsInMultipleAlbumsStateAndNotOnEndOfRange_WhenMainComponentSendsKeyPressedSignalMinus_ThenGuiLoadsTheNextSetOfAlbums)
{
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(fakeAlbums16));

    const int expectedIndex = defaultSelectedAlbumIndex + defaultAlbumStep;
    EXPECT_CALL(*mainComponentMock, loadMultipleAlbums(_, expectedIndex));
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(_, expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex));

    mainComponentMock->keyPressedSignal(keyMinus);
}

TEST_F(GuiTest, GivenGuiIsInMultipleAlbumsStateAndNotAtTheEndOfRange_WhenMainComponentSendsKeyPressedSignalPlus_ThenGuiLoadsThePreviousSetOfAlbums)
{
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(fakeAlbums16));

    //this block is needed as setup because we are at the begin so underflow would occur
    EXPECT_CALL(*mainComponentMock, loadMultipleAlbums(_, _));
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(_, _));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(_));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(_));
    mainComponentMock->keyPressedSignal(keyMinus);

    const int expectedIndex = defaultSelectedAlbumIndex;
    EXPECT_CALL(*mainComponentMock, loadMultipleAlbums(_, expectedIndex));
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(_, expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex));

    mainComponentMock->keyPressedSignal(keyPlus);
}

TEST_F(GuiTest, GivenGuiIsInMultipleAlbumsStateAndOnEndOfRange_WhenMainComponentSendsKeyPressedSignalPlus_ThenGuiLoadsTheLastSetOfAlbums)
{
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(fakeAlbums16));

    const int expectedIndex = defaultSelectedAlbumIndex + defaultAlbumStep;
    EXPECT_CALL(*mainComponentMock, loadMultipleAlbums(_, expectedIndex));
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(_, expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex));

    mainComponentMock->keyPressedSignal(keyPlus);
}

TEST_F(GuiTest, GivenGuiIsInMultipleAlbumsStateAndAtTheEndOfRange_WhenMainComponentSendsKeyPressedSignalMinus_ThenGuiLoadsTheFirstSetOfAlbums)
{
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(fakeAlbums16));

    //this block is needed as setup because we have to be at the end so overflow will occur
    EXPECT_CALL(*mainComponentMock, loadMultipleAlbums(_, _));
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(_, _));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(_));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(_));
    mainComponentMock->keyPressedSignal(keyMinus);

    const int expectedIndex = defaultSelectedAlbumIndex;
    EXPECT_CALL(*mainComponentMock, loadMultipleAlbums(_, expectedIndex));
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(_, expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex));

    mainComponentMock->keyPressedSignal(keyMinus);
}
//TODO test range edges (odd number of albums...)

TEST_F(GuiTest, GuiIsInSingleAlbumStateAndNotOnEndOfRange_WhenMainComponentSendsKeyPressedSignalMinus_ThenGuiLoadsTheNextAlbum)
{
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(fakeAlbums16));

    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());
    mainComponentMock->keyPressedSignal(keyH);

    const int expectedIndex = defaultSelectedAlbumIndex + 1;
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(_, expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex));

    mainComponentMock->keyPressedSignal(keyMinus);
}

TEST_F(GuiTest, GuiIsInSingleAlbumStateAndNotOnEndOfRange_WhenMainComponentSendsKeyPressedSignalPlus_ThenGuiLoadsThePreviousAlbum)
{
    ON_CALL(*fileSystemMock, getAlbums()).WillByDefault(testing::ReturnRef(fakeAlbums16));

    EXPECT_CALL(*mainComponentMock, switchBetweenAlbumViews());
    mainComponentMock->keyPressedSignal(keyH);
    //this block is needed as setup because we are at the begin so underflow would occur
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(_, _));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(_));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(_));
    mainComponentMock->keyPressedSignal(keyMinus);

    const int expectedIndex = defaultSelectedAlbumIndex;
    EXPECT_CALL(*mainComponentMock, loadSingleAlbum(_, expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateAlbumSelection(expectedIndex));
    EXPECT_CALL(*mainComponentMock, updateSongSelection(defaultSelectedSongIndex));

    mainComponentMock->keyPressedSignal(keyPlus);
}

//TODO test overflow, underflow
