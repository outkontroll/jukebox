#include "gtest/gtest.h"

#include "CreditManager.h"

using namespace jukebox::creditmanager;

class CreditManagerTest : public ::testing::Test
{    
protected:
    CreditManager creditManager;
};

namespace {
    constexpr unsigned zeroCredit(0);
    constexpr unsigned oneSongCredit(1);
    constexpr unsigned threeSongsCredit(3);
    constexpr unsigned oneAlbumCredit(18);
}

TEST_F(CreditManagerTest, empty)
{
    EXPECT_EQ(zeroCredit, creditManager.getCredits());
    EXPECT_FALSE(creditManager.hasEnoughCreditsToPlaySong());
    EXPECT_FALSE(creditManager.hasEnoughCreditsToPlayAlbum());
    EXPECT_FALSE(creditManager.startPlaySong());
    EXPECT_FALSE(creditManager.startPlayAlbum());
}

TEST_F(CreditManagerTest, insertSingle50)
{
    creditManager.coinInsert50();

    EXPECT_EQ(oneSongCredit, creditManager.getCredits());
    EXPECT_TRUE(creditManager.hasEnoughCreditsToPlaySong());
}

TEST_F(CreditManagerTest, insertSingle100)
{
    creditManager.coinInsert100();

    EXPECT_EQ(threeSongsCredit, creditManager.getCredits());
    EXPECT_FALSE(creditManager.hasEnoughCreditsToPlayAlbum());
}

TEST_F(CreditManagerTest, insertSingle200)
{
    creditManager.coinInsert200();

    EXPECT_EQ(oneAlbumCredit / 3, creditManager.getCredits());
}

TEST_F(CreditManagerTest, insertTriple200)
{
    creditManager.coinInsert200();
    creditManager.coinInsert200();
    creditManager.coinInsert200();

    EXPECT_EQ(oneAlbumCredit, creditManager.getCredits());
    EXPECT_TRUE(creditManager.hasEnoughCreditsToPlayAlbum());
}

TEST_F(CreditManagerTest, notEnoughCreditsToPlayAlbum_tooFewInserted)
{
    creditManager.coinInsert100();
    creditManager.coinInsert50();

    EXPECT_FALSE(creditManager.hasEnoughCreditsToPlayAlbum());
}

TEST_F(CreditManagerTest, startPlaySong_enoughCredits)
{
    creditManager.coinInsert50();

    EXPECT_TRUE(creditManager.startPlaySong());
}

TEST_F(CreditManagerTest, startPlayAlbum_enoughCredits)
{
    creditManager.coinInsert200();
    creditManager.coinInsert200();
    creditManager.coinInsert200();

    EXPECT_TRUE(creditManager.startPlayAlbum());
}

TEST_F(CreditManagerTest, creditIncrease_empty)
{
    creditManager.creditIncrease();

    EXPECT_EQ(oneSongCredit, creditManager.getCredits());
}

TEST_F(CreditManagerTest, creditIncrease_afterInsertion)
{
    creditManager.coinInsert50();
    creditManager.coinInsert100();

    creditManager.creditIncrease();

    EXPECT_EQ(5, creditManager.getCredits());
}

TEST_F(CreditManagerTest, creditDecrease_empy)
{
    creditManager.creditDecrease();

    EXPECT_EQ(zeroCredit, creditManager.getCredits());
}

TEST_F(CreditManagerTest, creditDecrease_afterInsertion)
{
    creditManager.coinInsert200();
    creditManager.coinInsert50();

    creditManager.creditDecrease();

    EXPECT_EQ(oneAlbumCredit / 3, creditManager.getCredits());
}
