#ifndef PASSWORD_H
#define PASSWORD_H

#include "JuceHeader.h"
#include "nlohmann/json.hpp"

namespace jukebox {

class Password
{
public:
    Password() = default;

    Password(const juce::String& plain);

    bool isMatching(const juce::String& plain) const;

    bool operator==(const Password& other) const;

private:
    friend void to_json(nlohmann::json& j, const Password& pw);
    friend void from_json(const nlohmann::json& j, Password& pw);
    juce::String password = "";
    juce::String salt = "";

    std::tuple<juce::String, juce::String> encrypt(const juce::String& plain);
};

}

#endif //PASSWORD_H
