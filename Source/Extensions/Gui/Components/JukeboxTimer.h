#ifndef JUKEBOXTIMER_H
#define JUKEBOXTIMER_H

#include "JuceHeader.h"
#include <functional>

namespace jukebox { namespace gui {

class JukeboxTimer : public juce::Timer
{
public:
    JukeboxTimer(std::function<void()> func);

    // Timer interface
    void timerCallback() override;

    void runOnce(int intervalInMilliseconds) noexcept;

private:
    std::function<void()> functionToCall;
    bool shouldRunOnce = false;
};

}}

#endif // JUKEBOXTIMER_H
