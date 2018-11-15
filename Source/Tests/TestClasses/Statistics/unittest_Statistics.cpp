#include "gtest/gtest.h"
#include <sstream>
#include <fstream>
#include "Statistics.h"
#include "Song.h"
#include "SongBuilder.h"
#include "JuceEventLoopRunner.h"

using namespace jukebox::statistics;
using namespace jukebox::audio;

namespace {
    static const Song song1{12, 3, "fakeFileName", "fakeVisibleName2"};
    static const Song song2{7, 15, "fakeFileName", "fakeVisibleName1"};
    static const Album album1{9, "fakeAlbumName1"};
    static const Album album2{8, "008"};
}

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

TEST(StatisticsTest1, baseClassCtorDtor)
{
    IStatistics* stat = new Statistics;

    delete stat;
}

TEST_F(StatisticsTest, empty)
{
    const auto insertedAll = statistics.getInsertedAll();
    const auto insertedSinceLastSave = statistics.getInsertedSinceLastSave();
    statistics.showStatistics(ss);
    
    ASSERT_EQ(0, insertedAll);
    ASSERT_EQ(0, insertedSinceLastSave);
    ASSERT_EQ("Inserted: 0\nInserted since last save: 0\n", ss.str());
}

TEST_F(StatisticsTest, playOneSong)
{
    const juce::File userHome("~");
    const auto song = jukebox::songbuilder::SongBuilder::buildSong(1, 1, userHome, "01 - fakeVisibleName2");
    statistics.songPlayed(song);
    
    statistics.showStatistics(ss);

    std::string expected("Inserted: 0\nInserted since last save: 0\n00101 - fakeVisibleName2: 1\n");
    ASSERT_EQ(expected, ss.str());
}
//TODO test other thing
TEST_F(StatisticsTest, playOneAlbum)
{
    statistics.albumPlayed(album1);
    
    statistics.showStatistics(ss);

    std::string expected("Inserted: 0\nInserted since last save: 0\nfakeAlbumName1: 1\n");
    ASSERT_EQ(expected, ss.str());
}

TEST_F(StatisticsTest, coinInsert50)
{
    statistics.coinInserted50();

    statistics.showStatistics(ss);

    std::string expected("Inserted: 50\nInserted since last save: 50\n");
    ASSERT_EQ(expected, ss.str());
}

TEST_F(StatisticsTest, coinInsert100)
{
    statistics.coinInserted100();

    statistics.showStatistics(ss);

    std::string expected("Inserted: 100\nInserted since last save: 100\n");
    ASSERT_EQ(expected, ss.str());
}

TEST_F(StatisticsTest, coinInsert200)
{
    statistics.coinInserted200();

    statistics.showStatistics(ss);

    std::string expected("Inserted: 200\nInserted since last save: 200\n");
    ASSERT_EQ(expected, ss.str());
}

TEST_F(StatisticsTest, multiplePlays)
{
    statistics.coinInserted50();
    statistics.songPlayed(song1);
    statistics.coinInserted200();
    statistics.albumPlayed(album1);
    statistics.coinInserted50();
    statistics.coinInserted50();
    statistics.coinInserted100();
    statistics.albumPlayed(album2);
    statistics.albumPlayed(album1);
    statistics.songPlayed(song1);
    statistics.songPlayed(song1);
    statistics.songPlayed(song2);
    
    statistics.showStatistics(ss);

    std::string expected("Inserted: 450\nInserted since last save: 450\n008: 1\nfakeAlbumName1: 2\nfakeVisibleName1: 1\nfakeVisibleName2: 3\n");
    ASSERT_EQ(expected, ss.str());
}

TEST_F(StatisticsTest, insertedCoinsTodayClear)
{
    JuceEventLoopRunner eventLoopRunner;
    const int timeToSave(100);
    statistics.coinInserted50();

    statistics.setSaveTimeout(timeToSave);

    eventLoopRunner.runEventLoop(timeToSave);

    statistics.showStatistics(ss);
    std::string expected("Inserted: 50\nInserted since last save: 0\n");
    ASSERT_EQ(expected, ss.str());

    ss.str("");
    statistics.coinInserted50();
    statistics.showStatistics(ss);
    expected = "Inserted: 100\nInserted since last save: 50\n";
    ASSERT_EQ(expected, ss.str());

    eventLoopRunner.runEventLoop(timeToSave);

    ss.str("");
    statistics.showStatistics(ss);
    expected = "Inserted: 100\nInserted since last save: 0\n";
    ASSERT_EQ(expected, ss.str());
}
