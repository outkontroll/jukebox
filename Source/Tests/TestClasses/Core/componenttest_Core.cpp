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
};

TEST_F(CoreTest, whenGuiSends50CoinInserted_thenCreditManagerGetsIt_GuiAndStatisticsRefresed)
{
    ON_CALL(*creditManagerMock, getCredits()).WillByDefault(Return(1));

    EXPECT_CALL(*creditManagerMock, coinInsert50());
    EXPECT_CALL(*creditManagerMock, getCredits());
    EXPECT_CALL(*guiMock, refreshCredits(1));
    EXPECT_CALL(*statisticsMock, coinInserted50());
    guiMock->coinInserted50Signal();
}

TEST_F(CoreTest, whenGuiSends100CoinInserted_thenCreditManagerGetsIt_GuiAndStatisticsRefresed)
{
    ON_CALL(*creditManagerMock, getCredits()).WillByDefault(Return(3));

    EXPECT_CALL(*creditManagerMock, coinInsert100());
    EXPECT_CALL(*creditManagerMock, getCredits());
    EXPECT_CALL(*guiMock, refreshCredits(3));
    EXPECT_CALL(*statisticsMock, coinInserted100());
    guiMock->coinInserted100Signal();
}

TEST_F(CoreTest, whenGuiSends200CoinInserted_thenCreditManagerGetsIt_GuiAndStatisticsRefresed)
{
    ON_CALL(*creditManagerMock, getCredits()).WillByDefault(Return(6));

    EXPECT_CALL(*creditManagerMock, coinInsert200());
    EXPECT_CALL(*creditManagerMock, getCredits());
    EXPECT_CALL(*guiMock, refreshCredits(6));
    EXPECT_CALL(*statisticsMock, coinInserted200());
    guiMock->coinInserted200Signal();
}
