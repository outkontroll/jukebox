#include "Settings.h"
#include <fstream>
#include "nlohmann/json.hpp"

using namespace jukebox::settings;
using json = nlohmann::json;

namespace {
    const auto jsonFileName = "settings.json";
}

struct jukebox::settings::PImpl
{
    PImpl() = default;

    PImpl(std::string musicDirectory_, int millisecsToPlaySong_, int millisecsToSaveInsertedCoins_)
        : musicDirectory(std::move(musicDirectory_)),
          millisecsToPlaySong(millisecsToPlaySong_),
          millisecsToSaveInsertedCoins(millisecsToSaveInsertedCoins_)
    {}

    std::string musicDirectory = "";
    int millisecsToPlaySong = 5000;
    int millisecsToSaveInsertedCoins = 24 * 3600 * 1000;
};

namespace jukebox::settings {
    inline void to_json(json& j, const PImpl& p)
    {
        j = json{{"musicDirectory", p.musicDirectory}, {"millisecsToPlaySong", p.millisecsToPlaySong}, {"millisecsToSaveInsertedCoins", p.millisecsToSaveInsertedCoins}};
    }

    inline void from_json(const json& j, PImpl& p)
    {
        if(j.find("musicDirectory") != j.end())
            p.musicDirectory = j.at("musicDirectory").get<std::string>();
        if(j.find("millisecsToPlaySong") != j.end())
            p.millisecsToPlaySong = j.at("millisecsToPlaySong").get<int>();
        if(j.find("millisecsToSaveInsertedCoins") != j.end())
            p.millisecsToSaveInsertedCoins = j.at("millisecsToSaveInsertedCoins").get<int>();
    }
}

Settings::Settings(std::string musicDirectory_)
 : data(std::make_unique<PImpl>(std::move(musicDirectory_), 5000, 24 * 3600 * 1000))
{
    deserialize();
}

Settings::~Settings() = default;

std::string Settings::getMusicDirectory() const
{
    return data->musicDirectory;
}

void Settings::setMusicDirectory(std::string musicDirectory_)
{
    data->musicDirectory = std::move(musicDirectory_);

    serialize();
}

int Settings::getTimeToPlaySong() const
{
    return data->millisecsToPlaySong;
}

void Settings::setTimeToPlaySong(int millisecsToPlaySong_)
{
    data->millisecsToPlaySong = millisecsToPlaySong_;

    serialize();
}

int Settings::getTimeToSaveInsertedCoins() const
{
    return data->millisecsToSaveInsertedCoins;
}

void Settings::setTimeToSaveInsertedCoins(int millisecs)
{
    data->millisecsToSaveInsertedCoins = millisecs;

    serialize();
}

void Settings::serialize()
{
    std::ofstream o(jsonFileName);
    if(o)
    {
        json j = *(data.get());
        o << j.dump(4) << std::endl;
    }
}

void Settings::deserialize()
{
    std::ifstream i(jsonFileName);
    if(i)
    {
        json j;
        i >> j;
        *data = j;
    }
}
