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

struct CoreTest : public ::testing::Test
{    
    void SetUp() override
    {
        core = std::make_unique<Core>(std::make_unique<GuiMock>(),
                                      std::make_unique<CreditManagerMock>(),
                                      std::make_unique<MusicPlayerMock>(),
                                      std::make_unique<StatisticsMock>(),
                                      std::make_unique<SettingsMock>());
    }
protected:
    std::unique_ptr<Core> core;
};

TEST_F(CoreTest, empty)
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
