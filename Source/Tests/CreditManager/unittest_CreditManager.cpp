#include "gtest/gtest.h"
#include "CreditManager.h"

using namespace jukebox::creditmanager;

class CreditManagerTest : public ::testing::Test
{    
protected:
    CreditManager creditManager;
};

TEST_F(CreditManagerTest, empty)
{
    unsigned int expected(0);
    EXPECT_EQ(expected, creditManager.getCredits());
    EXPECT_FALSE(creditManager.hasEnoughCreditsToPlaySong());
    EXPECT_FALSE(creditManager.hasEnoughCreditsToPlayAlbum());
    EXPECT_FALSE(creditManager.startPlaySong());
    EXPECT_FALSE(creditManager.startPlayAlbum());
}

TEST_F(CreditManagerTest, insertSingle50)
{
    creditManager.coinInsert50();

    unsigned int expected(1);
    EXPECT_EQ(expected, creditManager.getCredits());
}

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
