#include "gtest/gtest.h"
#include "Logger.h"

int main(int argc, char **argv)
{
    auto disabler(jukebox::log::Logger::getInstance().disableLog());
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
