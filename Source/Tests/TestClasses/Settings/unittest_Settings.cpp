#include "gtest/gtest.h"
#include "Settings.h"
#include <string>

using namespace jukebox::settings;

class SettingsTest : public ::testing::Test
{    
public:
    SettingsTest() : settings("fakeMusicDir"){}
protected:
    Settings settings;
};

TEST(SettingsTest1, baseClassCtorDtor)
{
    ISettings* sett = new Settings("fakeMusicDir");
    delete sett;
}

TEST_F(SettingsTest, WhenMusicDirectorySet_ThenItIsSet)
{
    settings.setMusicDirectory("/tmp");

    std::string expected("/tmp");
    EXPECT_EQ(expected, settings.getMusicDirectory());
}

TEST_F(SettingsTest, WhenTimeToPlaySet_ThenItIsSet)
{
    settings.setTimeToPlaySong(4000);

    EXPECT_EQ(4000, settings.getTimeToPlaySong());
}

TEST_F(SettingsTest, WhenTimeToSaveInsertedCoinsSet_ThenItIsSet)
{
    settings.setTimeToSaveInsertedCoins(12000);

    EXPECT_EQ(12000, settings.getTimeToSaveInsertedCoins());
}

TEST_F(SettingsTest, setMusicDir)
{
    std::string newMusicDir("fakeMusicDir");

    settings.setMusicDirectory(newMusicDir);

    EXPECT_EQ(newMusicDir, settings.getMusicDirectory());
}
