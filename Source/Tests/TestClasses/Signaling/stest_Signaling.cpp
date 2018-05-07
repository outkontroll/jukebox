#include "gtest/gtest.h"
#include <string>

#include "JukeboxTimer.h"
#include "JuceEventLoopRunner.h"
#include "FreeFunctions.h"
#include <chrono>
#include <thread>

#include <iostream>

using namespace jukebox;

namespace {
    constexpr int timerMillisecs = 100;
}

TEST(SignalingTest, Signaling2)
{
    JuceEventLoopRunner eventLoopRunner;

    FooMock fooMock;
    JukeboxTimer timer([&fooMock](){
        fooMock.foo();
    });
    EXPECT_CALL(fooMock, foo());

    timer.runOnce(timerMillisecs);
    eventLoopRunner.runEventLoop(timerMillisecs + 20);
}

