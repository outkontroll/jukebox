#include "JukeboxTimer.h"
#include "Song.h"

using namespace jukebox::gui;

JukeboxTimer::JukeboxTimer(std::function<void()> func)
    : functionToCall(std::move(func))
{
}

void JukeboxTimer::timerCallback()
{
    if(shouldRunOnce)
    {
        stopTimer();
        shouldRunOnce = false;
    }

    functionToCall();
}

void JukeboxTimer::runOnce(int intervalInMilliseconds) noexcept
{
    shouldRunOnce = true;

    startTimer(intervalInMilliseconds);
}
