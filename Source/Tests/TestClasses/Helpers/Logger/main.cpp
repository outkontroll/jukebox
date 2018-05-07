#include "gtest/gtest.h"
#include <fstream>
#include "Logger.h"

namespace {
    const auto testFileName = "loggerTest.txt";
}

int main(int argc, char **argv)
{
    {
        std::ofstream ofs;
        ofs.open(testFileName, std::ofstream::out | std::ofstream::trunc);
        ofs.close();
    }

    LOG_INITIALIZE(testFileName);

    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
