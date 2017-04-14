#include "gtest/gtest.h"
#include "Statistics.h"
#include <sstream>

using namespace jukebox::statistics;
using namespace jukebox::audio;

class StatisticsTest : public ::testing::Test
{
protected:
    virtual void SetUp()
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
    
    EXPECT_EQ("", ss.str());
}

TEST_F(StatisticsTest, playOneSong)
{
    statistics.songPlayed(Song(12, 3));
    
    statistics.showStatistics(ss);

    std::string expected("01203: 1\n");
    EXPECT_EQ(expected, ss.str());
}

TEST_F(StatisticsTest, playOneAlbum)
{
    statistics.albumPlayed(Album(9));
    
    statistics.showStatistics(ss);

    std::string expected("00900: 1\n");
    EXPECT_EQ(expected, ss.str());
}

TEST_F(StatisticsTest, multiplePlays)
{
    statistics.songPlayed(Song(12, 3));
    statistics.albumPlayed(Album(9));
    statistics.albumPlayed(Album(8));
    statistics.albumPlayed(Album(9));
    statistics.songPlayed(Song(12, 3));
    statistics.songPlayed(Song(12, 3));
    
    statistics.showStatistics(ss);

    std::string expected("00800: 1\n00900: 2\n01203: 3\n");
    EXPECT_EQ(expected, ss.str());
}
