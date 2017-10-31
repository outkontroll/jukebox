#ifndef JUKEBOXTIMER_H
#define JUKEBOXTIMER_H

#include "JuceHeader.h"
#include <functional>

namespace jukebox { namespace audio {
    class Song;
}}

namespace jukebox { namespace gui {

class JukeboxTimer : public juce::Timer
{
public:
    JukeboxTimer(std::function<void()> func);

    // Timer interface
    void timerCallback() override;

private:
    std::function<void()> functionToCall;
};

}}

#endif // JUKEBOXTIMER_H
