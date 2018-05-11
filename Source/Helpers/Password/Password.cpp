#include "Password.h"
#include <tuple>
#include "nlohmann/json.hpp"
#include "Logger.h"

using namespace nlohmann;
using namespace juce;
using namespace jukebox;

namespace nlohmann {
    template <>
    struct adl_serializer<juce::String>
    {
        static void to_json(json& j, const juce::String& s)
        {
            j = s.toStdString();
        }

        static void from_json(const json& j, juce::String& s)
        {
            s = j.get<std::string>();
        }
    };
}

Password::Password(const String& plain)
{
    std::tie(password, salt) = encrypt(plain);
}

bool Password::isMatching(const juce::String& plain) const
{
    return !password.isEmpty() && password.compare(juce::SHA256((plain + salt).toUTF8()).toHexString()) == 0;
}

bool Password::isValid() const
{
    return !password.isEmpty() && !salt.isEmpty();
}

namespace jukebox {

void to_json(json& j, const Password& pw)
{
    j = json{{"password", pw.password}, {"salt", pw.salt}};
}

void from_json(const json& j, Password& pw)
{
    if(j.find("password") == j.end() || j.find("salt") == j.end())
    {
        LOG_ERROR("invalid password in json file");
        return;
    }

    const auto password_ = j.at("password").get<std::string>();
    const auto salt_ = j.at("salt").get<std::string>();
    pw.password = password_;
    pw.salt = salt_;
}

}

bool Password::operator==(const Password& other) const
{
    return password == other.password && salt == other.salt;
}

std::tuple<juce::String, juce::String> Password::encrypt(const juce::String& plain)
{
    juce::BigInteger maxValue;
    maxValue.setBit(256);
    const auto random_salt = juce::Random::getSystemRandom().nextLargeNumber(maxValue).toString(16);

    return std::make_tuple(juce::SHA256((plain + random_salt).toUTF8()).toHexString(), random_salt);
}
