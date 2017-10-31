#include "JukeboxTimer.h"
#include "Song.h"

using namespace jukebox::gui;

JukeboxTimer::JukeboxTimer(std::function<void()> func)
    : functionToCall(std::move(func))
{
}

void JukeboxTimer::timerCallback()
{
    functionToCall();
}
