#include "gtest/gtest.h"
#include "Core.h"
#include "Logger.h"
#include "GuiMock.h"
#include "CreditManagerMock.h"
#include "MusicPlayerMock.h"
#include "StatisticsMock.h"
#include "SettingsMock.h"
#include <memory>

using namespace jukebox::core;
using namespace testing;

struct CoreTest : public Test
{    
    void SetUp() override
    {
        auto gui = std::make_unique<NiceMock<GuiMock>>();
        guiMock = gui.get();
        auto creditManager = std::make_unique<NiceMock<CreditManagerMock>>();
        creditManagerMock = creditManager.get();
        auto musicPlayer = std::make_unique<NiceMock<MusicPlayerMock>>();
        musicPlayerMock = musicPlayer.get();
        auto statistics = std::make_unique<NiceMock<StatisticsMock>>();
        statisticsMock = statistics.get();
        auto settings = std::make_unique<NiceMock<SettingsMock>>();
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
};

TEST_F(CoreTest, whenSetup_thenSetMusicFolderOfGuiIsCalled_withSettingsMusicFolder)
{

    /*
    unsigned int expected(0);
    EXPECT_EQ(expected, creditManager.getCredits());
    EXPECT_FALSE(creditManager.hasEnoughCreditsToPlaySong());
    EXPECT_FALSE(creditManager.hasEnoughCreditsToPlayAlbum());
    EXPECT_FALSE(creditManager.startPlaySong());
    EXPECT_FALSE(creditManager.startPlayAlbum());
    */
}

TEST_F(CoreTest, insertSingle50)
{
    /*creditManager.coinInsert50();
    unsigned int expected(1);
    EXPECT_EQ(expected, creditManager.getCredits());*/
}
/*
TEST_F(CreditManagerTest, insertSingle100)
{
    creditManager.coinInsert100();

    unsigned int expected(3);
    EXPECT_EQ(expected, creditManager.getCredits());
}

TEST_F(CreditManagerTest, insertSingle200)
{
    creditManager.coinInsert200();

    unsigned int expected(6);
    EXPECT_EQ(expected, creditManager.getCredits());
}
*/
