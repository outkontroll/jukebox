#include <string>
#include <fstream>
#include "gtest/gtest.h"
#include "Settings.h"
#include "Password.h"

using namespace jukebox::settings;
using namespace jukebox;

namespace {
    const char* jsonFileName = "settings.json";
}

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

inline void truncateJSONfile()
{
    std::ofstream ofs;
    ofs.open(jsonFileName, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

TEST(SettingsTest1, emptyJSONfile)
{
    truncateJSONfile();
    Settings settings("fakeMusicDir");

    ASSERT_EQ("fakeMusicDir", settings.getMusicDirectory());
    ASSERT_FALSE(settings.isPasswordSet());
}

inline void createJunkJSONfile()
{
    std::ofstream o(jsonFileName);
    if(o)
    {
        nlohmann::json j;
        j["musicDirectory"] = "junk";
        o << j.dump(4) << std::endl;
    }
}

TEST(SettingsTest1, wrongJSONfileFormat)
{
    createJunkJSONfile();
    Settings settings("fakeMusicDir");

    ASSERT_NE("junk", settings.getMusicDirectory());
}

inline void createWrongPasswordedJSONfile()
{
    std::ofstream o(jsonFileName);
    if(o)
    {
        nlohmann::json j = R"({
                           "millisecsToPlaySong": 4000,
                           "millisecsToSaveInsertedCoins": 12000,
                           "musicDirectory": "fakeMusicDir",
                           "password": {
                               "password" : null,
                               "salt" : null
                           }
                       })"_json;
        o << j.dump(4) << std::endl;
    }
}

TEST(SettingsTest1, wrongPasswordFormatInJSONfile)
{
    createWrongPasswordedJSONfile();
    Settings settings("fakeMusicDir");

    ASSERT_EQ(nullptr, settings.getPassword());
}

inline void createEmptyPasswordedJSONfile()
{
    std::ofstream o(jsonFileName);
    if(o)
    {
        nlohmann::json j = R"({
                           "millisecsToPlaySong": 4000,
                           "millisecsToSaveInsertedCoins": 12000,
                           "musicDirectory": "fakeMusicDir",
                           "password": {
                               "password" : null
                           }
                       })"_json;
        o << j.dump(4) << std::endl;
    }
}

TEST(SettingsTest1, emptyPasswordFormatInJSONfile)
{
    createEmptyPasswordedJSONfile();
    Settings settings("fakeMusicDir");

    ASSERT_FALSE(settings.getPassword()->isValid());
}

inline void createCorrectPasswordedJSONfile()
{
    std::ofstream o(jsonFileName);
    if(o)
    {
        nlohmann::json j = R"({
                           "millisecsToPlaySong": 4000,
                           "millisecsToSaveInsertedCoins": 12000,
                           "musicDirectory": "fakeMusicDir",
                           "password": {
                               "password" : "fakePassword",
                               "salt" : "fakeSalt"
                           }
                       })"_json;
        o << j.dump(4) << std::endl;
    }
}

TEST(SettingsTest1, correctPasswordFormatInJSONfile)
{
    createCorrectPasswordedJSONfile();
    Settings settings("fakeMusicDir");

    ASSERT_FALSE(settings.getPassword()->isMatching("fakePassword"));
}

TEST_F(SettingsTest, WhenMusicDirectorySet_ThenItIsSet)
{
    settings.setMusicDirectory("/tmp");

    std::string expected("/tmp");
    ASSERT_EQ(expected, settings.getMusicDirectory());
}

TEST_F(SettingsTest, WhenTimeToPlaySet_ThenItIsSet)
{
    settings.setTimeToPlaySong(4000);

    ASSERT_EQ(4000, settings.getTimeToPlaySong());
}

TEST_F(SettingsTest, WhenTimeToSaveInsertedCoinsSet_ThenItIsSet)
{
    settings.setTimeToSaveInsertedCoins(12000);

    ASSERT_EQ(12000, settings.getTimeToSaveInsertedCoins());
}

TEST_F(SettingsTest, setMusicDir)
{
    std::string newMusicDir("fakeMusicDir");

    settings.setMusicDirectory(newMusicDir);

    ASSERT_EQ(newMusicDir, settings.getMusicDirectory());
}

TEST_F(SettingsTest, setPassword)
{
    Password password("abcdefg");

    settings.setPassword(password);

    ASSERT_TRUE(settings.isPasswordSet());
    ASSERT_EQ(password, *settings.getPassword());
}

TEST_F(SettingsTest, turnOffPassword)
{
    Password password("abcdefg");
    settings.setPassword(password);

    settings.turnOffPassword();

    ASSERT_FALSE(settings.isPasswordSet());
    ASSERT_EQ(nullptr, settings.getPassword());
}
