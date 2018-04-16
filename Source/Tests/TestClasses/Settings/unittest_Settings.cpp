#include "gtest/gtest.h"
#include "Settings.h"
#include <string>

using namespace jukebox::settings;

class SettingsTest : public ::testing::Test
{    
public:
    SettingsTest()
        : settings("/tmp")
    {
    }

protected:
    Settings settings;
};

TEST_F(SettingsTest, musicDir)
{
    std::string expected("/tmp");
    EXPECT_EQ(expected, settings.getMusicDirectory());
}

TEST_F(SettingsTest, setMusicDir)
{
    std::string newMusicDir("fakeMusicDir");

    settings.setMusicDirectory(newMusicDir);

    EXPECT_EQ(newMusicDir, settings.getMusicDirectory());
}
