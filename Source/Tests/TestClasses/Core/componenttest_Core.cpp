#include <memory>
#include <sstream>
#include "gtest/gtest.h"
#include "Core.h"
#include "Logger.h"
#include "FileSystemMock.h"
#include "GuiMock.h"
#include "CreditManagerMock.h"
#include "MusicPlayerMock.h"
#include "StatisticsMock.h"
#include "SettingsMock.h"
#include "FreeFunctions.h"
#include "MusicPlayerExceptions.h"
#include "Password.h"

using namespace jukebox;
using namespace jukebox::core;
using namespace jukebox::audio;
using namespace testing;
using namespace std;

struct CoreTest : public Test
{    
    void SetUp() override
    {
        auto filesys = make_unique<StrictMock<FileSystemMock>>();
        fileSystemMock = filesys.get();
        auto gui = make_unique<StrictMock<GuiMock>>();
        guiMock = gui.get();
        auto creditManager = make_unique<StrictMock<CreditManagerMock>>();
        creditManagerMock = creditManager.get();
        auto musicPlayer = make_unique<StrictMock<MusicPlayerMock>>();
        musicPlayerMock = musicPlayer.get();
        auto statistics = make_unique<StrictMock<StatisticsMock>>();
        statisticsMock = statistics.get();
        auto settings = make_unique<StrictMock<SettingsMock>>();
        settingsMock = settings.get();

        Password fakePassword{"fakePassword"};

        EXPECT_CALL(*settingsMock, getMusicDirectory()).Times(2).WillRepeatedly(Return("FakeMusicDirectory"));
        EXPECT_CALL(*settingsMock, getTimeToPlaySong()).WillOnce(Return(5000));
        EXPECT_CALL(*settingsMock, getTimeToSaveInsertedCoins()).Times(2).WillRepeatedly(Return(24 * 3600 * 1000));
        EXPECT_CALL(*settingsMock, isPasswordSet()).WillOnce(Return(true));
        EXPECT_CALL(*settingsMock, getPassword()).WillOnce(Return(fakePassword));
        //TODO check order of the calls as it matters
        EXPECT_CALL(*fileSystemMock, loadAlbums(std::string_view("FakeMusicDirectory")));
        EXPECT_CALL(*guiMock, setFileSystem(fileSystemMock));
        EXPECT_CALL(*guiMock, setMusicFolder("FakeMusicDirectory"));
        EXPECT_CALL(*guiMock, setTimeToPlaySong(5000));
        EXPECT_CALL(*guiMock, setTimeToSaveInsertedCoins(24 * 3600 * 1000));
        EXPECT_CALL(*guiMock, setPassword(fakePassword));
        EXPECT_CALL(*statisticsMock, setSaveTimeout(24 * 3600 * 1000));

        core = make_unique<Core>(move(gui),
                                 move(creditManager),
                                 move(musicPlayer),
                                 move(statistics),
                                 move(settings),
                                 move(filesys));
    }
protected:
    unique_ptr<Core> core;

    StrictMock<FileSystemMock>* fileSystemMock;
    StrictMock<GuiMock>* guiMock;
    StrictMock<CreditManagerMock>* creditManagerMock;
    StrictMock<MusicPlayerMock>* musicPlayerMock;
    StrictMock<StatisticsMock>* statisticsMock;
    StrictMock<SettingsMock>* settingsMock;

    jukebox::signals::Slot eventsSlot;
};

// insertCoin

TEST_F(CoreTest, WhenGuiSends50CoinInserted_ThenCreditManagerGetsItAndGuiAndStatisticsRefreshed)
{
    EXPECT_CALL(*creditManagerMock, coinInsert50());
    EXPECT_CALL(*creditManagerMock, getCredits()).WillOnce(Return(1));
    EXPECT_CALL(*guiMock, refreshCredits(1));
    EXPECT_CALL(*statisticsMock, coinInserted50());
    guiMock->coinInserted50Signal();
}

TEST_F(CoreTest, WhenGuiSends100CoinInserted_ThenCreditManagerGetsItAndGuiAndStatisticsRefreshed)
{
    EXPECT_CALL(*creditManagerMock, coinInsert100());
    EXPECT_CALL(*creditManagerMock, getCredits()).WillOnce(Return(3));
    EXPECT_CALL(*guiMock, refreshCredits(3));
    EXPECT_CALL(*statisticsMock, coinInserted100());

    guiMock->coinInserted100Signal();
}

TEST_F(CoreTest, WhenGuiSends200CoinInserted_ThenCreditManagerGetsItAndGuiAndStatisticsRefreshed)
{
    EXPECT_CALL(*creditManagerMock, coinInsert200());
    EXPECT_CALL(*creditManagerMock, getCredits()).WillOnce(Return(6));
    EXPECT_CALL(*guiMock, refreshCredits(6));
    EXPECT_CALL(*statisticsMock, coinInserted200());

    guiMock->coinInserted200Signal();
}

// playSong

TEST_F(CoreTest, GivenHasEnoughCreditsAndMusicPlayerIsNotPlaying_WhenGuiSendsSongToPlay_ThenPlaysMusicAndCreditManagerDecreaseCreditsAndGuiAndStatisticsRefreshed)
{
    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlaySong()).WillOnce(Return(true));
    EXPECT_CALL(*musicPlayerMock, isPlaying()).WillOnce(Return(false));
    EXPECT_CALL(*creditManagerMock, startPlaySong());
    EXPECT_CALL(*musicPlayerMock, playSong(song.fileName));
    EXPECT_CALL(*statisticsMock, songPlayed(song));
    EXPECT_CALL(*creditManagerMock, getCredits()).WillOnce(Return(13));
    EXPECT_CALL(*guiMock, refreshCredits(13));
    EXPECT_CALL(*guiMock, setCurrentlyPlayedSong(song));

    guiMock->playSongSignal(song);
}

TEST_F(CoreTest, GivenHasEnoughCreditsAndMusicPlayerIsNotPlayingAndThrowsException_WhenGuiSendsSongToPlay_ThenPlaysMusicAndCreditManagerDecreaseCreditsAndGuiAndStatisticsRefreshed)
{
    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlaySong()).Times(2).WillRepeatedly(Return(true));
    EXPECT_CALL(*musicPlayerMock, isPlaying()).Times(2).WillRepeatedly(Return(false));
    EXPECT_CALL(*creditManagerMock, startPlaySong()).Times(2);
    EXPECT_CALL(*statisticsMock, songPlayed(song)).Times(2);
    EXPECT_CALL(*creditManagerMock, getCredits()).Times(2).WillRepeatedly(Return(13));
    EXPECT_CALL(*guiMock, refreshCredits(13)).Times(2);
    EXPECT_CALL(*guiMock, showStatusMessage(ResourceId::ErrorDuringSongPlaying)).Times(2);
    EXPECT_CALL(*musicPlayerMock, playSong(song.fileName)).Times(2)
            .WillOnce(Throw(FileNotFoundException()))
            .WillOnce(Throw(FormatReaderException()));

    guiMock->playSongSignal(song);
    guiMock->playSongSignal(song);
}

TEST_F(CoreTest, GivenHasNotEnoughCredits_WhenGuiSendsSongToPlay_ThenGuiGetsNotification)
{
    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlaySong()).WillOnce(Return(false));
    EXPECT_CALL(*guiMock, showStatusMessage(ResourceId::ErrorFewCreditsSong));

    guiMock->playSongSignal(song);
}

TEST_F(CoreTest, GivenHasEnoughCreditsAndMusicPlayerIsPlaying_WhenGuiSendsSongToPlay_ThenEnqueInGuiAndCreditManagerDecreaseCreditsAndGuiAndStatisticsRefreshed)
{
    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlaySong()).WillOnce(Return(true));
    EXPECT_CALL(*musicPlayerMock, isPlaying()).WillOnce(Return(true));
    EXPECT_CALL(*creditManagerMock, startPlaySong());
    EXPECT_CALL(*statisticsMock, songPlayed(song));
    EXPECT_CALL(*creditManagerMock, getCredits()).WillOnce(Return(13));
    EXPECT_CALL(*guiMock, refreshCredits(13));
    EXPECT_CALL(*guiMock, enqueue(song));

    guiMock->playSongSignal(song);
}

// playAlbum

TEST_F(CoreTest, GivenHasEnoughCreditsAndMusicPlayerIsNotPlaying_WhenGuiSendsSingleSongToPlayAlbum_ThenPlaysMusicAndCreditManagerDecreaseCreditsAndGuiAndStatisticsRefreshed)
{
    Song song{1, 1, "fakeFileName", "fakeVisibleName"};
    Album album{song.albumNumber, "fakeAlbumName"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum()).WillOnce(Return(true));
    EXPECT_CALL(*musicPlayerMock, isPlaying()).WillOnce(Return(false));
    EXPECT_CALL(*creditManagerMock, startPlayAlbum());
    EXPECT_CALL(*musicPlayerMock, playSong(song.fileName));
    EXPECT_CALL(*statisticsMock, albumPlayed(album));
    EXPECT_CALL(*statisticsMock, songPlayed(song));
    EXPECT_CALL(*creditManagerMock, getCredits()).WillOnce(Return(13));
    EXPECT_CALL(*guiMock, refreshCredits(13));
    EXPECT_CALL(*guiMock, setCurrentlyPlayedSong(song));

    guiMock->playAlbumSignal(album, {song});
}

TEST_F(CoreTest, GivenHasEnoughCreditsAndMusicPlayerIsNotPlayingAndThrowsException_WhenGuiSendsSingleSongToPlayAlbum_ThenPlaysMusicAndCreditManagerDecreaseCreditsAndGuiAndStatisticsRefreshed)
{
    Song song{1, 1, "fakeFileName", "fakeVisibleName"};
    Album album{song.albumNumber, "fakeAlbumName"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum()).Times(2).WillRepeatedly(Return(true));
    EXPECT_CALL(*musicPlayerMock, isPlaying()).Times(2).WillRepeatedly(Return(false));
    EXPECT_CALL(*creditManagerMock, startPlayAlbum()).Times(2);
    EXPECT_CALL(*statisticsMock, albumPlayed(album)).Times(2);
    EXPECT_CALL(*statisticsMock, songPlayed(song)).Times(2);
    EXPECT_CALL(*creditManagerMock, getCredits()).Times(2).WillRepeatedly(Return(13));
    EXPECT_CALL(*guiMock, refreshCredits(13)).Times(2);
    EXPECT_CALL(*guiMock, showStatusMessage(ResourceId::ErrorDuringSongPlaying)).Times(2);
    EXPECT_CALL(*musicPlayerMock, playSong(song.fileName)).Times(2)
            .WillOnce(Throw(FileNotFoundException()))
            .WillOnce(Throw(FormatReaderException()));

    guiMock->playAlbumSignal(album, {song});
    guiMock->playAlbumSignal(album, {song});
}

TEST_F(CoreTest, GivenHasEnoughCreditsAndMusicPlayerIsPlaying_WhenGuiSendsSingleSongToPlayAlbum_ThenEnqueInGuiAndCreditManagerDecreaseCreditsAndGuiAndStatisticsRefreshed)
{
    Song song{1, 1, "fakeFileName", "fakeVisibleName"};
    Album album{song.albumNumber, "fakeAlbumName"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum()).WillOnce(Return(true));
    EXPECT_CALL(*musicPlayerMock, isPlaying()).WillOnce(Return(true));
    EXPECT_CALL(*creditManagerMock, startPlayAlbum());
    EXPECT_CALL(*statisticsMock, albumPlayed(album));
    EXPECT_CALL(*statisticsMock, songPlayed(song));
    EXPECT_CALL(*creditManagerMock, getCredits()).WillOnce(Return(13));
    EXPECT_CALL(*guiMock, refreshCredits(13));
    EXPECT_CALL(*guiMock, enqueue(song));

    guiMock->playAlbumSignal(album, {song});
}

TEST_F(CoreTest, GivenHasEnoughCreditsAndMusicPlayerIsNotPlaying_WhenGuiSendsMultipleSongToPlayAlbum_ThenPlaysFirstMusicEnqueOthersInGuiAndCreditManagerDecreaseCreditsAndGuiAndStatisticsRefreshed)
{
    Song song1{1, 1, "fakeFileName", "fakeVisibleName"};
    Song song2{1, 2, "fakeFileName", "fakeVisibleName"};
    Song song3{1, 3, "fakeFileName", "fakeVisibleName"};
    Album album{song1.albumNumber, "fakeAlbumName"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum()).WillOnce(Return(true));
    EXPECT_CALL(*creditManagerMock, startPlayAlbum());
    EXPECT_CALL(*creditManagerMock, getCredits()).WillOnce(Return(13));
    EXPECT_CALL(*guiMock, refreshCredits(13));
    EXPECT_CALL(*musicPlayerMock, isPlaying()).WillOnce(Return(false)).WillRepeatedly(Return(true));
    EXPECT_CALL(*statisticsMock, albumPlayed(album));
    EXPECT_CALL(*statisticsMock, songPlayed(song1));
    EXPECT_CALL(*guiMock, setCurrentlyPlayedSong(song1));
    EXPECT_CALL(*musicPlayerMock, playSong(song1.fileName));
    EXPECT_CALL(*statisticsMock, songPlayed(song2));
    EXPECT_CALL(*guiMock, enqueue(song2));
    EXPECT_CALL(*statisticsMock, songPlayed(song3));
    EXPECT_CALL(*guiMock, enqueue(song3));

    guiMock->playAlbumSignal(album, {song1, song2, song3});
}

TEST_F(CoreTest, GivenHasEnoughCreditsAndMusicPlayerIsPlaying_WhenGuiSendsMultipleSongToPlayAlbum_ThenEnqueAllMusicInGuiAndCreditManagerDecreaseCreditsAndGuiAndStatisticsRefreshed)
{
    Song song1{1, 1, "fakeFileName", "fakeVisibleName"};
    Song song2{1, 2, "fakeFileName", "fakeVisibleName"};
    Song song3{1, 3, "fakeFileName", "fakeVisibleName"};
    Album album{song1.albumNumber, "fakeAlbumName"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum()).WillOnce(Return(true));
    EXPECT_CALL(*creditManagerMock, startPlayAlbum());
    EXPECT_CALL(*creditManagerMock, getCredits()).WillOnce(Return(13));
    EXPECT_CALL(*guiMock, refreshCredits(13));
    EXPECT_CALL(*statisticsMock, albumPlayed(album));
    EXPECT_CALL(*musicPlayerMock, isPlaying()).WillRepeatedly(Return(true));
    EXPECT_CALL(*statisticsMock, songPlayed(song1));
    EXPECT_CALL(*guiMock, enqueue(song1));
    EXPECT_CALL(*statisticsMock, songPlayed(song2));
    EXPECT_CALL(*guiMock, enqueue(song2));
    EXPECT_CALL(*statisticsMock, songPlayed(song3));
    EXPECT_CALL(*guiMock, enqueue(song3));

    guiMock->playAlbumSignal(album, {song1, song2, song3});
}

TEST_F(CoreTest, GivenHasNotEnoughCredits_WhenGuiSendsAlbumToPlay_ThenGuiGetsNotification)
{
    Album album{1, "fakeAlbumName"};
    Song song{1, 2, "fake1", "fake2"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum()).WillOnce(Return(false));
    EXPECT_CALL(*guiMock, showStatusMessage(ResourceId::ErrorFewCreditsAlbum));

    guiMock->playAlbumSignal(album, {song});
}

TEST_F(CoreTest, GivenHasEnoughCredits_WhenGuiSendsZeroAlbumNumToPlayAlbum_ThenGuiGetsNotification)
{
    Album album{0, "fakeAlbumName"};
    Song song{1, 2, "fake1", "fake2"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum()).WillOnce(Return(true));
    EXPECT_CALL(*guiMock, showStatusMessage(ResourceId::ErrorDuringAlbumPlaying));

    guiMock->playAlbumSignal(album, {song});
}

TEST_F(CoreTest, GivenHasEnoughCredits_WhenGuiSendsEmptyVectorOfSongsToPlayAlbum_ThenGuiGetsNotification)
{
    Album album{1, "fakeAlbumName"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum()).WillOnce(Return(true));
    EXPECT_CALL(*guiMock, showStatusMessage(ResourceId::ErrorDuringAlbumPlaying));

    guiMock->playAlbumSignal(album, {});
}

// playNextSong

TEST_F(CoreTest, GivenMusicPlayerIsNotPlaying_WhenGuiSendsPlayNextSong_ThenMusicPlayerStartsPlayingAndGuiGetsRefreshed)
{
    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*musicPlayerMock, isPlaying()).WillOnce(Return(false));
    EXPECT_CALL(*musicPlayerMock, playSong(song.fileName));
    EXPECT_CALL(*guiMock, setCurrentlyPlayedSong(song));

    guiMock->playNextSongSignal(song);
}

TEST_F(CoreTest, GivenMusicPlayerIsPlaying_WhenGuiSendsPlayNextSong_ThenGuiGetsError)
{
    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*musicPlayerMock, isPlaying()).WillOnce(Return(true));
    EXPECT_CALL(*guiMock, showStatusMessage(ResourceId::ErrorDuringSongPlaying));

    guiMock->playNextSongSignal(song);
}

TEST_F(CoreTest, GivenMusicPlayerIsNotPlayingAndThrows_WhenGuiSendsPlayNextSong_ThenMusicPlayerStartsPlayingAndGuiRemovesCurrentSongAndGetsErrors)
{
    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*musicPlayerMock, isPlaying()).Times(2).WillRepeatedly(Return(false));
    EXPECT_CALL(*guiMock, showStatusMessage(ResourceId::ErrorDuringSongPlaying)).Times(2);
    EXPECT_CALL(*guiMock, removeCurrentSong()).Times(2);
    EXPECT_CALL(*musicPlayerMock, playSong(song.fileName)).Times(2)
            .WillOnce(Throw(FileNotFoundException()))
            .WillOnce(Throw(FormatReaderException()));

    guiMock->playNextSongSignal(song);
    guiMock->playNextSongSignal(song);
}

// removePlayed

TEST_F(CoreTest, GivenMusicPlayerIsPlaying_WhenGuiSendsRemovePlayedSong_ThenMusicStops)
{
    EXPECT_CALL(*musicPlayerMock, isPlaying()).WillOnce(Return(true));
    EXPECT_CALL(*musicPlayerMock, stopPlaying());

    guiMock->removePlayedSongSignal();
}

TEST_F(CoreTest, GivenMusicPlayerIsNotPlaying_WhenGuiSendsRemovePlayedSong_ThenGuiGetsWarning)
{
    EXPECT_CALL(*musicPlayerMock, isPlaying()).WillOnce(Return(false));
    EXPECT_CALL(*guiMock, showStatusMessage(ResourceId::WarningNotPlayingSong));

    guiMock->removePlayedSongSignal();
}

// finishedPlaying

TEST_F(CoreTest, WhenMusicPlayerSendsFinishedPlaying_ThenGuiRemovesCurrentSong)
{
    EXPECT_CALL(*guiMock, removeCurrentSong());

    musicPlayerMock->finishedPlayingSignal();
}

// creditIncrease

TEST_F(CoreTest, WhenGuiSendsCreditIncrease_ThenCreditManagerAndGuiUpdated)
{
    EXPECT_CALL(*creditManagerMock, getCredits()).WillOnce(Return(1));
    EXPECT_CALL(*creditManagerMock, creditIncrease());
    EXPECT_CALL(*guiMock, refreshCredits(1));

    guiMock->creditIncreaseSignal();
}

// creaditDecraese


TEST_F(CoreTest, WhenGuiSendsCreditDecrease_ThenCreditManagerAndGuiUpdated)
{
    EXPECT_CALL(*creditManagerMock, getCredits()).WillOnce(Return(1));
    EXPECT_CALL(*creditManagerMock, creditDecrease());
    EXPECT_CALL(*guiMock, refreshCredits(1));

    guiMock->creditDecreaseSignal();
}

TEST_F(CoreTest, WhenGuiSendsRequestStatistics_ThenGuiGetsItFromStatisticsAndUpdatesGui)
{
    std::string stat("fakeStatistics");
    std::stringstream ss;
    EXPECT_CALL(*statisticsMock, showStatistics(_)).WillOnce(Invoke([&](ostream& ss_){ss_ << stat;}));
    EXPECT_CALL(*guiMock, showStatistics(stat));

    guiMock->requestStatisticsSignal();
}

// exitRequest

TEST_F(CoreTest, GivenMusicPlayerIsPlaying_WhenGuiSendsExit_ThenMusicPlayerStopsPlayingAndExitSignalIsCalled)
{
    FooMock fooMock;
    eventsSlot.connect(&fooMock, &FooMock::foo, core->exitRequestedSignal);

    EXPECT_CALL(*musicPlayerMock, isPlaying()).WillOnce(Return(true));
    EXPECT_CALL(*guiMock, prepareForExit());
    EXPECT_CALL(*musicPlayerMock, stopPlaying());
    EXPECT_CALL(fooMock, foo());

    guiMock->exitRequestedSignal();
}

TEST_F(CoreTest, GivenMusicPlayerIsNotPlaying_WhenGuiSendsExit_ThenExitSignalIsCalled)
{
    FooMock fooMock;
    eventsSlot.connect(&fooMock, &FooMock::foo, core->exitRequestedSignal);

    EXPECT_CALL(*musicPlayerMock, isPlaying()).WillOnce(Return(false));
    EXPECT_CALL(fooMock, foo());

    guiMock->exitRequestedSignal();
}

// musicDirectoryChanged

TEST_F(CoreTest, WhenGuiSendsMusicDirectoryChangedSignal_ThenSettingsIsNotified)
{
    std::string foo("fakeMusicDirectory");
    EXPECT_CALL(*settingsMock, setMusicDirectory(foo));
    EXPECT_CALL(*guiMock, setMusicFolder(foo));
    EXPECT_CALL(*fileSystemMock, loadAlbums(std::string_view(foo)));

    guiMock->musicDirectoryChangedSignal(foo);
}

// timeToPlayASongChanged

TEST_F(CoreTest, WhenGuiSendsTimeToPlayASongChangedSignal_ThenSettingsIsNotified)
{
    EXPECT_CALL(*settingsMock, setTimeToPlaySong(2000));
    EXPECT_CALL(*guiMock, setTimeToPlaySong(2000));

    guiMock->timeToPlayASongChangedSignal(2000);
}

TEST_F(CoreTest, GivenOnlyNonNegativeNumbersAccepted_WhenGuiSendsTimeToPlayASongChangedSignal_ThenAnErrorIsDisplayed)
{
    EXPECT_CALL(*guiMock, showStatusMessage(ResourceId::ErrorNegativeNumber));

    guiMock->timeToPlayASongChangedSignal(-2000);
}

// timeToSaveInsertedCoinsChanged

TEST_F(CoreTest, WhenGuiSendsTimeToSaveInsertedCoinsChangedSignal_ThenSettingsIsNotified)
{
    EXPECT_CALL(*settingsMock, setTimeToSaveInsertedCoins(12000));
    EXPECT_CALL(*guiMock, setTimeToSaveInsertedCoins(12000));
    EXPECT_CALL(*statisticsMock, setSaveTimeout(12000));

    guiMock->timeToSaveInsertedCoinsChangedSignal(12000);
}

TEST_F(CoreTest, GivenOnlyGreaterOrEqual3600Accepted_WhenGuiSendsTimeToSaveInsertedCoinsChangedSignal_ThenAnErrorIsDisplayed)
{
    EXPECT_CALL(*guiMock, showStatusMessage(ResourceId::ErrorWrongNumber)).Times(2);

    guiMock->timeToSaveInsertedCoinsChangedSignal(-2000);
    guiMock->timeToSaveInsertedCoinsChangedSignal(3599);
}
