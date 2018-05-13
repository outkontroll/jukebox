#include "Settings.h"
#include <fstream>
#include <optional>
#include "nlohmann/json.hpp"
#include "Password.h"
#include "Logger.h"

using namespace jukebox::settings;
using json = nlohmann::json;

namespace {
    const auto jsonFileName = "settings.json";
}

namespace nlohmann {
    template<>
    struct adl_serializer<std::optional<jukebox::Password>>
    {
        static void to_json(json& j, const std::optional<jukebox::Password>& opt);
        static void from_json(const json& j, std::optional<jukebox::Password>& opt);
    };

void adl_serializer<std::optional<jukebox::Password>>::to_json(json& j, const std::optional<jukebox::Password>& opt)
{
    if (opt == std::nullopt)
    {
        j = nullptr;
    }
    else
    {
        j = *opt;
    }
}

void adl_serializer<std::optional<jukebox::Password>>::from_json(const json& j, std::optional<jukebox::Password>& opt)
{
    if (j.is_null())
    {
        opt =  std::nullopt;
    }
    else
    {
        opt = j.get<jukebox::Password>();
    }
}

}

struct jukebox::settings::PImpl
{
    PImpl() = default;

    PImpl(std::string musicDirectory_)
        : musicDirectory(std::move(musicDirectory_))
    {}

    std::string musicDirectory = "";
    int millisecsToPlaySong = 5000;
    int millisecsToSaveInsertedCoins = 24 * 3600 * 1000;
    int millisecsToPlayAdvertiseMusic = 20 * 60 * 1000;
    std::optional<Password> password = std::nullopt;
};

namespace jukebox::settings {
    inline void to_json(json& j, const PImpl& p)
    {
        j = json{{"musicDirectory", p.musicDirectory},
                 {"millisecsToPlaySong", p.millisecsToPlaySong},
                 {"millisecsToSaveInsertedCoins", p.millisecsToSaveInsertedCoins},
                 {"millisecsToPlayAdvertiseMusic", p.millisecsToPlayAdvertiseMusic},
                 {"password", p.password}};
    }

    inline void from_json(const json& j, PImpl& p)
    {
        if(j.find("musicDirectory") != j.end() &&
           j.find("millisecsToPlaySong") != j.end() &&
           j.find("millisecsToSaveInsertedCoins") != j.end() &&
           j.find("millisecsToPlayAdvertiseMusic") != j.end() &&
           j.find("password") != j.end())
        {
            PImpl pp;
            pp.musicDirectory = j.at("musicDirectory").get<std::string>();
            pp.millisecsToPlaySong = j.at("millisecsToPlaySong").get<int>();
            pp.millisecsToSaveInsertedCoins = j.at("millisecsToSaveInsertedCoins").get<int>();
            pp.millisecsToPlayAdvertiseMusic = j.at("millisecsToPlayAdvertiseMusic").get<int>();
            pp.password = j.at("password").get<std::optional<Password>>();

            std::swap(p, pp);
        }
        else
        {
            LOG_ERROR("Invalid settings in json file");
        }
    }
}

Settings::Settings(std::string musicDirectory_)
 : data(std::make_unique<PImpl>(std::move(musicDirectory_)))
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

int Settings::getTimeToPlayAdvertiseMusic() const
{
    return data->millisecsToPlayAdvertiseMusic;
}

void Settings::setTimeToPlayAdvertiseMusic(int millisecs)
{
    data->millisecsToPlayAdvertiseMusic = millisecs;

    serialize();
}

bool Settings::isPasswordSet() const
{
    return data->password.has_value();
}

void Settings::turnOffPassword()
{
    data->password.reset();

    serialize();
}

const jukebox::Password* Settings::getPassword() const
{
    return data->password.has_value() ? &data->password.value() : nullptr;
}

void Settings::setPassword(const jukebox::Password& password)
{
    data->password = password;

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
        try
        {
            json j;
            i >> j;
            *data = j;
        }
        catch(std::exception& e)
        {
            LOG_ERROR(e.what());
        }
    }
}
