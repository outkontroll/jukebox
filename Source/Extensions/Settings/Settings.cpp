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

    PImpl(std::string musicDirectory_, int millisecsToPlaySong_)
        : musicDirectory(std::move(musicDirectory_)),
          millisecsToPlaySong(millisecsToPlaySong_)
    {}

    std::string musicDirectory = "";
    int millisecsToPlaySong = 5000;
};

namespace jukebox::settings {
    void to_json(json& j, const PImpl& p)
    {
        j = json{{"musicDirectory", p.musicDirectory}, {"millisecsToPlaySong", p.millisecsToPlaySong}};
    }

    void from_json(const json& j, PImpl& p)
    {
        p.musicDirectory = j.at("musicDirectory").get<std::string>();
        p.millisecsToPlaySong = j.at("millisecsToPlaySong").get<int>();
    }
}

Settings::Settings(std::string musicDirectory_)
 : data(std::make_unique<PImpl>(std::move(musicDirectory_), 5000))
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
