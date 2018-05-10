#include "Password.h"
#include <tuple>
#include "nlohmann/json.hpp"

using namespace nlohmann;
using namespace juce;
using namespace jukebox;

namespace nlohmann {
    template <>
    struct adl_serializer<juce::String>
    {
        static void to_json(json& j, const juce::String& s)
        {
            j = s;
        }

        static void from_json(const json& j, juce::String& s)
        {
            s = j.get<juce::String>();
        }
    };
}

Password::Password(const String& plain)
{
    std::tie(password, salt) = encrypt(plain);
}

bool Password::isMatching(const juce::String& plain) const
{
    return password.compare(juce::SHA256((plain + salt).toUTF8()).toHexString()) == 0;
}

void Password::to_json(json& j, const Password& pw)
{
    j = json{{"password", pw.password}, {"salt", pw.salt}};
}

void Password::from_json(const json& j, Password& pw)
{
    pw.password = j.at("password").get<juce::String>();
    pw.salt = j.at("salt").get<juce::String>();
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
