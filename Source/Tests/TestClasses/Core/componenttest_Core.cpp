#include "gtest/gtest.h"
#include "Core.h"
#include "Logger.h"
#include "GuiMock.h"
#include "CreditManagerMock.h"
#include "MusicPlayerMock.h"
#include "StatisticsMock.h"
#include "SettingsMock.h"
#include "FreeFunctions.h"
#include "MusicPlayerExceptions.h"
#include <memory>

using namespace jukebox;
using namespace jukebox::core;
using namespace jukebox::audio;
using namespace testing;
using namespace std;

struct CoreTest : public Test
{    
    void SetUp() override
    {
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

        std::string musicDirectory("fakeMusicDirectory");
        EXPECT_CALL(*settingsMock, getMusicDirectory()).WillOnce(Return(musicDirectory));
        EXPECT_CALL(*guiMock, setMusicFolder(musicDirectory)).Times(1);

        core = make_unique<Core>(move(gui),
                                 move(creditManager),
                                 move(musicPlayer),
                                 move(statistics),
                                 move(settings));
    }
protected:
    unique_ptr<Core> core;

    StrictMock<GuiMock>* guiMock;
    StrictMock<CreditManagerMock>* creditManagerMock;
    StrictMock<MusicPlayerMock>* musicPlayerMock;
    StrictMock<StatisticsMock>* statisticsMock;
    StrictMock<SettingsMock>* settingsMock;

    jukebox::signals::Slot eventsSlot;
};

// insertCoin

TEST_F(CoreTest, whenGuiSends50CoinInserted_thenCreditManagerGetsIt_GuiAndStatisticsRefreshed)
{
    ON_CALL(*creditManagerMock, getCredits()).WillByDefault(Return(1));

    EXPECT_CALL(*creditManagerMock, coinInsert50());
    EXPECT_CALL(*creditManagerMock, getCredits());
    EXPECT_CALL(*guiMock, refreshCredits(1));
    EXPECT_CALL(*statisticsMock, coinInserted50());
    guiMock->coinInserted50Signal();
}

TEST_F(CoreTest, whenGuiSends100CoinInserted_thenCreditManagerGetsIt_GuiAndStatisticsRefreshed)
{
    ON_CALL(*creditManagerMock, getCredits()).WillByDefault(Return(3));

    EXPECT_CALL(*creditManagerMock, coinInsert100());
    EXPECT_CALL(*creditManagerMock, getCredits());
    EXPECT_CALL(*guiMock, refreshCredits(3));
    EXPECT_CALL(*statisticsMock, coinInserted100());

    guiMock->coinInserted100Signal();
}

TEST_F(CoreTest, whenGuiSends200CoinInserted_thenCreditManagerGetsIt_GuiAndStatisticsRefreshed)
{
    ON_CALL(*creditManagerMock, getCredits()).WillByDefault(Return(6));

    EXPECT_CALL(*creditManagerMock, coinInsert200());
    EXPECT_CALL(*creditManagerMock, getCredits());
    EXPECT_CALL(*guiMock, refreshCredits(6));
    EXPECT_CALL(*statisticsMock, coinInserted200());

    guiMock->coinInserted200Signal();
}

// playSong

TEST_F(CoreTest, whenGuiSendsSongToPlay_HasEnoughCreditsAndMusicPlayerIsNotPlaying_thenPlaysMusicAndCreditManagerDecreaseCredits_GuiAndStatisticsRefreshed)
{
    ON_CALL(*creditManagerMock, hasEnoughCreditsToPlaySong()).WillByDefault(Return(true));
    ON_CALL(*musicPlayerMock, isPlaying()).WillByDefault(Return(false));
    ON_CALL(*creditManagerMock, getCredits()).WillByDefault(Return(13));

    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlaySong());
    EXPECT_CALL(*musicPlayerMock, isPlaying());
    EXPECT_CALL(*creditManagerMock, startPlaySong());
    EXPECT_CALL(*musicPlayerMock, playSong(song.fileName));
    EXPECT_CALL(*statisticsMock, songPlayed(song));
    EXPECT_CALL(*creditManagerMock, getCredits());
    EXPECT_CALL(*guiMock, refreshCredits(13));
    EXPECT_CALL(*guiMock, setCurrentlyPlayedSong(song));

    guiMock->playSongSignal(song);
}

TEST_F(CoreTest, whenGuiSendsSongToPlay_HasEnoughCredits_AndMusicPlayerIsNotPlayingAndThrowsException_thenPlaysMusicAndCreditManagerDecreaseCredits_GuiAndStatisticsRefreshed)
{
    ON_CALL(*creditManagerMock, hasEnoughCreditsToPlaySong()).WillByDefault(Return(true));
    ON_CALL(*musicPlayerMock, isPlaying()).WillByDefault(Return(false));
    ON_CALL(*creditManagerMock, getCredits()).WillByDefault(Return(13));
    ON_CALL(*musicPlayerMock, playSong(_)).WillByDefault(Throw(FileNotFoundException()));

    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlaySong()).Times(2);
    EXPECT_CALL(*musicPlayerMock, isPlaying()).Times(2);
    EXPECT_CALL(*creditManagerMock, startPlaySong()).Times(2);
    EXPECT_CALL(*musicPlayerMock, playSong(song.fileName)).Times(2);
    EXPECT_CALL(*statisticsMock, songPlayed(song)).Times(2);
    EXPECT_CALL(*creditManagerMock, getCredits()).Times(2);
    EXPECT_CALL(*guiMock, refreshCredits(13)).Times(2);
    EXPECT_CALL(*guiMock, showStatusMessage(ResourceId::ErrorDuringSongPlaying)).Times(2);

    guiMock->playSongSignal(song);

    ON_CALL(*musicPlayerMock, playSong(_)).WillByDefault(Throw(FormatReaderException()));
    guiMock->playSongSignal(song);
}

TEST_F(CoreTest, whenGuiSendsSongToPlay_HasNotEnoughCredits_thenGuiGetsNotification)
{
    ON_CALL(*creditManagerMock, hasEnoughCreditsToPlaySong()).WillByDefault(Return(false));

    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlaySong());
    EXPECT_CALL(*guiMock, showStatusMessage(ResourceId::ErrorFewCreditsSong));

    guiMock->playSongSignal(song);
}

TEST_F(CoreTest, whenGuiSendsSongToPlay_HasEnoughCreditsAndMusicPlayerIsPlaying_thenEnqueInGuiAndCreditManagerDecreaseCredits_GuiAndStatisticsRefreshed)
{
    ON_CALL(*creditManagerMock, hasEnoughCreditsToPlaySong()).WillByDefault(Return(true));
    ON_CALL(*musicPlayerMock, isPlaying()).WillByDefault(Return(true));
    ON_CALL(*creditManagerMock, getCredits()).WillByDefault(Return(13));

    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlaySong());
    EXPECT_CALL(*musicPlayerMock, isPlaying());
    EXPECT_CALL(*creditManagerMock, startPlaySong());
    EXPECT_CALL(*statisticsMock, songPlayed(song));
    EXPECT_CALL(*creditManagerMock, getCredits());
    EXPECT_CALL(*guiMock, refreshCredits(13));
    EXPECT_CALL(*guiMock, enqueue(song));

    guiMock->playSongSignal(song);
}

// playAlbum
//TODO

TEST_F(CoreTest, whenGuiSendsSingleSongToPlayAlbum_HasEnoughCreditsAndMusicPlayerIsNotPlaying_thenPlaysMusicAndCreditManagerDecreaseCredits_GuiAndStatisticsRefreshed)
{
    ON_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum()).WillByDefault(Return(true));
    ON_CALL(*musicPlayerMock, isPlaying()).WillByDefault(Return(false));
    ON_CALL(*creditManagerMock, getCredits()).WillByDefault(Return(13));

    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum());
    EXPECT_CALL(*musicPlayerMock, isPlaying());
    EXPECT_CALL(*creditManagerMock, startPlayAlbum());
    EXPECT_CALL(*musicPlayerMock, playSong(song.fileName));
    EXPECT_CALL(*statisticsMock, songPlayed(song));
    EXPECT_CALL(*creditManagerMock, getCredits());
    EXPECT_CALL(*guiMock, refreshCredits(13));
    EXPECT_CALL(*guiMock, setCurrentlyPlayedSong(song));

    guiMock->playAlbumSignal({song});
}

TEST_F(CoreTest, whenGuiSendsSingleSongToPlayAlbum_HasEnoughCredits_AndMusicPlayerIsNotPlayingAndThrowsException_thenPlaysMusicAndCreditManagerDecreaseCredits_GuiAndStatisticsRefreshed)
{
    ON_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum()).WillByDefault(Return(true));
    ON_CALL(*musicPlayerMock, isPlaying()).WillByDefault(Return(false));
    ON_CALL(*creditManagerMock, getCredits()).WillByDefault(Return(13));
    ON_CALL(*musicPlayerMock, playSong(_)).WillByDefault(Throw(FileNotFoundException()));

    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum()).Times(2);
    EXPECT_CALL(*musicPlayerMock, isPlaying()).Times(2);
    EXPECT_CALL(*creditManagerMock, startPlayAlbum()).Times(2);
    EXPECT_CALL(*musicPlayerMock, playSong(song.fileName)).Times(2);
    EXPECT_CALL(*statisticsMock, songPlayed(song)).Times(2);
    EXPECT_CALL(*creditManagerMock, getCredits()).Times(2);
    EXPECT_CALL(*guiMock, refreshCredits(13)).Times(2);
    EXPECT_CALL(*guiMock, showStatusMessage(ResourceId::ErrorDuringSongPlaying)).Times(2);

    guiMock->playAlbumSignal({song});

    ON_CALL(*musicPlayerMock, playSong(_)).WillByDefault(Throw(FormatReaderException()));
    guiMock->playAlbumSignal({song});
}

TEST_F(CoreTest, whenGuiSendsSingleSongToPlayAlbum_HasEnoughCreditsAndMusicPlayerIsPlaying_thenEnqueInGuiAndCreditManagerDecreaseCredits_GuiAndStatisticsRefreshed)
{
    ON_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum()).WillByDefault(Return(true));
    ON_CALL(*musicPlayerMock, isPlaying()).WillByDefault(Return(true));
    ON_CALL(*creditManagerMock, getCredits()).WillByDefault(Return(13));

    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum());
    EXPECT_CALL(*musicPlayerMock, isPlaying());
    EXPECT_CALL(*creditManagerMock, startPlayAlbum());
    EXPECT_CALL(*statisticsMock, songPlayed(song));
    EXPECT_CALL(*creditManagerMock, getCredits());
    EXPECT_CALL(*guiMock, refreshCredits(13));
    EXPECT_CALL(*guiMock, enqueue(song));

    guiMock->playAlbumSignal({song});
}

TEST_F(CoreTest, whenGuiSendsMultipleSongToPlayAlbum_HasEnoughCreditsAndMusicPlayerIsNotPlaying_thenPlaysFirstMusicEnqueOthersInGuiAndCreditManagerDecreaseCredits_GuiAndStatisticsRefreshed)
{
    ON_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum()).WillByDefault(Return(true));
    ON_CALL(*creditManagerMock, getCredits()).WillByDefault(Return(13));

    Song song1{1, 1, "fakeFileName", "fakeVisibleName"};
    Song song2{1, 2, "fakeFileName", "fakeVisibleName"};
    Song song3{1, 3, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum());
    EXPECT_CALL(*creditManagerMock, startPlayAlbum());
    EXPECT_CALL(*creditManagerMock, getCredits());
    EXPECT_CALL(*guiMock, refreshCredits(13));
    EXPECT_CALL(*musicPlayerMock, isPlaying()).WillOnce(Return(false)).WillRepeatedly(Return(true));
    EXPECT_CALL(*statisticsMock, songPlayed(song1));
    EXPECT_CALL(*guiMock, setCurrentlyPlayedSong(song1));
    EXPECT_CALL(*musicPlayerMock, playSong(song1.fileName));
    EXPECT_CALL(*statisticsMock, songPlayed(song2));
    EXPECT_CALL(*guiMock, enqueue(song2));
    EXPECT_CALL(*statisticsMock, songPlayed(song3));
    EXPECT_CALL(*guiMock, enqueue(song3));

    guiMock->playAlbumSignal({song1, song2, song3});
}

TEST_F(CoreTest, whenGuiSendsMultipleSongToPlayAlbum_HasEnoughCreditsAndMusicPlayerIsPlaying_thenEnqueAllMusicInGuiAndCreditManagerDecreaseCredits_GuiAndStatisticsRefreshed)
{
    ON_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum()).WillByDefault(Return(true));
    ON_CALL(*creditManagerMock, getCredits()).WillByDefault(Return(13));

    Song song1{1, 1, "fakeFileName", "fakeVisibleName"};
    Song song2{1, 2, "fakeFileName", "fakeVisibleName"};
    Song song3{1, 3, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum());
    EXPECT_CALL(*creditManagerMock, startPlayAlbum());
    EXPECT_CALL(*creditManagerMock, getCredits());
    EXPECT_CALL(*guiMock, refreshCredits(13));
    EXPECT_CALL(*musicPlayerMock, isPlaying()).WillRepeatedly(Return(true));
    EXPECT_CALL(*statisticsMock, songPlayed(song1));
    EXPECT_CALL(*guiMock, enqueue(song1));
    EXPECT_CALL(*statisticsMock, songPlayed(song2));
    EXPECT_CALL(*guiMock, enqueue(song2));
    EXPECT_CALL(*statisticsMock, songPlayed(song3));
    EXPECT_CALL(*guiMock, enqueue(song3));

    guiMock->playAlbumSignal({song1, song2, song3});
}

TEST_F(CoreTest, whenGuiSendsEmptyVectorOfSongsToPlayAlbum_HasEnoughCredits_thenGuiGetsNotification)
{
    ON_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum()).WillByDefault(Return(true));

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum());
    EXPECT_CALL(*guiMock, showStatusMessage(ResourceId::ErrorDuringAlbumPlaying));

    guiMock->playAlbumSignal({});
}

TEST_F(CoreTest, whenGuiSendsAlbumToPlay_HasNotEnoughCredits_thenGuiGetsNotification)
{
    ON_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum()).WillByDefault(Return(false));

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum());
    EXPECT_CALL(*guiMock, showStatusMessage(ResourceId::ErrorFewCreditsAlbum));

    guiMock->playAlbumSignal({});
}

// playNextSong
TEST_F(CoreTest, whenGuiSendsPlayNextSong_AndMusicPlayerIsNotPlaying_thenMusicPlayerStartsPlaying_AndGuiGetsRefreshed)
{
    ON_CALL(*musicPlayerMock, isPlaying()).WillByDefault(Return(false));

    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*musicPlayerMock, isPlaying());
    EXPECT_CALL(*musicPlayerMock, playSong(song.fileName));
    EXPECT_CALL(*guiMock, setCurrentlyPlayedSong(song));

    guiMock->playNextSongSignal(song);
}

TEST_F(CoreTest, whenGuiSendsPlayNextSong_AndMusicPlayerIsPlaying_thenGuiGetsError)
{
    ON_CALL(*musicPlayerMock, isPlaying()).WillByDefault(Return(true));

    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*musicPlayerMock, isPlaying());
    EXPECT_CALL(*guiMock, showStatusMessage(ResourceId::ErrorDuringSongPlaying));

    guiMock->playNextSongSignal(song);
}

TEST_F(CoreTest, whenGuiSendsPlayNextSong_AndMusicPlayerIsNotPlaying_AndMusicPlayerThrows_thenMusicPlayerStartsPlaying_AndGuiRemovesCurrentSongAndGetsErrors)
{
    ON_CALL(*musicPlayerMock, isPlaying()).WillByDefault(Return(false));
    ON_CALL(*musicPlayerMock, playSong(_)).WillByDefault(Throw(FileNotFoundException()));

    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*musicPlayerMock, isPlaying()).Times(2);
    EXPECT_CALL(*musicPlayerMock, playSong(song.fileName)).Times(2);
    EXPECT_CALL(*guiMock, showStatusMessage(ResourceId::ErrorDuringSongPlaying)).Times(2);
    EXPECT_CALL(*guiMock, removeCurrentSong()).Times(2);

    guiMock->playNextSongSignal(song);

    ON_CALL(*musicPlayerMock, playSong(_)).WillByDefault(Throw(FormatReaderException()));
    guiMock->playNextSongSignal(song);
}


// removePlayed

TEST_F(CoreTest, whenGuiSendsRemovePlayedSong_AndMusicPlayerIsPlaying_thenMusicStops)
{
    ON_CALL(*musicPlayerMock, isPlaying()).WillByDefault(Return(true));

    EXPECT_CALL(*musicPlayerMock, isPlaying());
    EXPECT_CALL(*musicPlayerMock, stopPlaying());

    guiMock->removePlayedSongSignal();
}

TEST_F(CoreTest, whenGuiSendsRemovePlayedSong_AndMusicPlayerIsNotPlaying_thenGuiGetsWarning)
{
    ON_CALL(*musicPlayerMock, isPlaying()).WillByDefault(Return(false));

    EXPECT_CALL(*musicPlayerMock, isPlaying());
    EXPECT_CALL(*guiMock, showStatusMessage(ResourceId::WarningNotPlayingSong));

    guiMock->removePlayedSongSignal();
}

// finishedPlaying

TEST_F(CoreTest, whenMusicPlayerSendsFinishedPlaying_thenGuiRemovesCurrentSong)
{
    EXPECT_CALL(*guiMock, removeCurrentSong());

    musicPlayerMock->finishedPlayingSignal();
}

// exitRequest

TEST_F(CoreTest, whenGuiSendsExit_AndMusicPlayerIsPlaying_thenMusicPlayerStopsPlaying_AndExitSignalIsCalled)
{
    ON_CALL(*musicPlayerMock, isPlaying()).WillByDefault(Return(true));
    FooMock fooMock;
    eventsSlot.connect(&fooMock, &FooMock::foo, core->exitRequestedSignal);

    EXPECT_CALL(*musicPlayerMock, isPlaying());
    EXPECT_CALL(*guiMock, prepareForExit());
    EXPECT_CALL(*musicPlayerMock, stopPlaying());
    EXPECT_CALL(fooMock, foo());

    guiMock->exitRequestedSignal();
}

TEST_F(CoreTest, whenGuiSendsExit_AndMusicPlayerIsNotPlaying_thenExitSignalIsCalled)
{
    ON_CALL(*musicPlayerMock, isPlaying()).WillByDefault(Return(false));
    FooMock fooMock;
    eventsSlot.connect(&fooMock, &FooMock::foo, core->exitRequestedSignal);

    EXPECT_CALL(*musicPlayerMock, isPlaying());
    EXPECT_CALL(fooMock, foo());

    guiMock->exitRequestedSignal();
}

// musicDirectoryChanged

TEST_F(CoreTest, whenGuiSendsMusicDirectoryChangedSignal_thenSettingsIsNotified)
{
    std::string foo("fakeMusicDirectory");
    EXPECT_CALL(*settingsMock, setMusicDirectory(foo));
    EXPECT_CALL(*guiMock, setMusicFolder(foo));

    guiMock->musicDirectoryChangedSignal(foo);
}
