#include "gtest/gtest.h"
#include <memory>
#include "ICreditManager.h"
#include "DllLoader/DllLoader.hpp"

using namespace jukebox::creditmanager;

namespace {
    const char* creditManagerAlternative = "creditManagerFree";
}

class CreditManagerFreeTest : public ::testing::Test
{    
public:
    CreditManagerFreeTest()
    {
        jukebox::DllLoader loader;
        creditManager = loader.load<ICreditManager>(creditManagerAlternative);
    }

protected:
    std::shared_ptr<ICreditManager> creditManager;
};

namespace {
    constexpr unsigned zeroCredit(0);
}

TEST_F(CreditManagerFreeTest, empty)
{
    EXPECT_EQ(zeroCredit, creditManager->getCredits());
    EXPECT_TRUE(creditManager->hasEnoughCreditsToPlaySong());
    EXPECT_TRUE(creditManager->hasEnoughCreditsToPlayAlbum());
    EXPECT_TRUE(creditManager->startPlaySong());
    EXPECT_TRUE(creditManager->startPlayAlbum());
}

TEST_F(CreditManagerFreeTest, insertSingle50)
{
    creditManager->coinInsert50();

    EXPECT_TRUE(creditManager->hasEnoughCreditsToPlaySong());
}

TEST_F(CreditManagerFreeTest, DISABLED_insertSingle100)
{
    creditManager->coinInsert100();

    EXPECT_TRUE(creditManager->hasEnoughCreditsToPlayAlbum());
}

TEST_F(CreditManagerFreeTest, DISABLED_insertSingle200)
{
    creditManager->coinInsert200();

    EXPECT_TRUE(creditManager->hasEnoughCreditsToPlayAlbum());
}

TEST_F(CreditManagerFreeTest, DISABLED_creditIncrease_empty)
{
    creditManager->creditIncrease();

    EXPECT_EQ(zeroCredit, creditManager->getCredits());
}

TEST_F(CreditManagerFreeTest, DISABLED_creditDecrease_empy)
{
    creditManager->creditDecrease();

    EXPECT_EQ(zeroCredit, creditManager->getCredits());
}
