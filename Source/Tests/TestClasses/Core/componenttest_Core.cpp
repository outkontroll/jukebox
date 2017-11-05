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

struct CoreTest : public Test
{    
    void SetUp() override
    {
        auto gui = std::make_unique<StrictMock<GuiMock>>();
        guiMock = gui.get();
        auto creditManager = std::make_unique<StrictMock<CreditManagerMock>>();
        creditManagerMock = creditManager.get();
        auto musicPlayer = std::make_unique<StrictMock<MusicPlayerMock>>();
        musicPlayerMock = musicPlayer.get();
        auto statistics = std::make_unique<StrictMock<StatisticsMock>>();
        statisticsMock = statistics.get();
        auto settings = std::make_unique<StrictMock<SettingsMock>>();
        settingsMock = settings.get();

        EXPECT_CALL(*guiMock, setMusicFolder(settings->getMusicDirectory())).Times(1);

        core = std::make_unique<Core>(std::move(gui),
                                      std::move(creditManager),
                                      std::move(musicPlayer),
                                      std::move(statistics),
                                      std::move(settings));
    }
protected:
    std::unique_ptr<Core> core;

    GuiMock* guiMock;
    CreditManagerMock* creditManagerMock;
    MusicPlayerMock* musicPlayerMock;
    StatisticsMock* statisticsMock;
    SettingsMock* settingsMock;

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
    EXPECT_CALL(*musicPlayerMock, playSong(song.getFileName()));
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
    EXPECT_CALL(*musicPlayerMock, playSong(song.getFileName())).Times(2);
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

TEST_F(CoreTest, whenGuiSendsAlbumToPlay_HasNotEnoughCredits_thenGuiGetsNotification)
{
    ON_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum()).WillByDefault(Return(false));

    Album album(1);

    EXPECT_CALL(*creditManagerMock, hasEnoughCreditsToPlayAlbum());
    EXPECT_CALL(*guiMock, showStatusMessage(ResourceId::ErrorFewCreditsAlbum));

    guiMock->playAlbumSignal(album);
}

// playNextSong
TEST_F(CoreTest, whenGuiSendsPlayNextSong_AndMusicPlayerIsNotPlaying_thenMusicPlayerStartsPlaying_AndGuiGetsRefreshed)
{
    ON_CALL(*musicPlayerMock, isPlaying()).WillByDefault(Return(false));

    Song song{1, 1, "fakeFileName", "fakeVisibleName"};

    EXPECT_CALL(*musicPlayerMock, isPlaying());
    EXPECT_CALL(*musicPlayerMock, playSong(song.getFileName()));
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
    EXPECT_CALL(*musicPlayerMock, playSong(song.getFileName())).Times(2);
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
