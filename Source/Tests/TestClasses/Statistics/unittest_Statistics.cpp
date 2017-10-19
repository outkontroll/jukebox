#include "gtest/gtest.h"
#include "Statistics.h"
#include <sstream>

using namespace jukebox::statistics;
using namespace jukebox::audio;

class StatisticsTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        ss.str("");
    }
    
protected:
    Statistics statistics;
    
    static std::ostringstream ss;
};

std::ostringstream StatisticsTest::ss;

TEST_F(StatisticsTest, empty)
{
    statistics.showStatistics(ss);
    
    EXPECT_EQ("Inserted: 0\n", ss.str());
}

TEST_F(StatisticsTest, playOneSong)
{
    statistics.songPlayed(Song(12, 3));
    
    statistics.showStatistics(ss);

    std::string expected("Inserted: 0\n01203: 1\n");
    EXPECT_EQ(expected, ss.str());
}

TEST_F(StatisticsTest, playOneAlbum)
{
    statistics.albumPlayed(Album(9));
    
    statistics.showStatistics(ss);

    std::string expected("Inserted: 0\n00900: 1\n");
    EXPECT_EQ(expected, ss.str());
}

TEST_F(StatisticsTest, coinInsert50)
{
    statistics.coinInserted50();

    statistics.showStatistics(ss);

    std::string expected("Inserted: 50\n");
    EXPECT_EQ(expected, ss.str());
}

TEST_F(StatisticsTest, coinInsert100)
{
    statistics.coinInserted100();

    statistics.showStatistics(ss);

    std::string expected("Inserted: 100\n");
    EXPECT_EQ(expected, ss.str());
}

TEST_F(StatisticsTest, coinInsert200)
{
    statistics.coinInserted200();

    statistics.showStatistics(ss);

    std::string expected("Inserted: 200\n");
    EXPECT_EQ(expected, ss.str());
}

TEST_F(StatisticsTest, multiplePlays)
{
    statistics.coinInserted50();
    statistics.songPlayed(Song(12, 3));
    statistics.coinInserted200();
    statistics.albumPlayed(Album(9));
    statistics.coinInserted50();
    statistics.coinInserted50();
    statistics.coinInserted100();
    statistics.albumPlayed(Album(8));
    statistics.albumPlayed(Album(9));
    statistics.songPlayed(Song(12, 3));
    statistics.songPlayed(Song(12, 3));
    
    statistics.showStatistics(ss);

    std::string expected("Inserted: 450\n00800: 1\n00900: 2\n01203: 3\n");
    EXPECT_EQ(expected, ss.str());
}
