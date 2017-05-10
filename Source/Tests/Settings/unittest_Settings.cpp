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
