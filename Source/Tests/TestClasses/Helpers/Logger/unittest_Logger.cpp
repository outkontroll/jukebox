#include "gtest/gtest.h"
#include <fstream>
#include "Logger.h"

using namespace jukebox;
using namespace jukebox::log;

namespace {
    //const auto testFileName = "loggerTest.txt";
}

void testFunctionName1();

void testFunctionName1()
{
    LOG_INFO("");
}

namespace foo{
    void testFunctionName2();

    void testFunctionName2()
    {
        LOG_INFO("");
    }

    namespace baz{
        void testFunctionName3();

        void testFunctionName3()
        {
            LOG_INFO("");
        }
    }
}

TEST(LoggerTest, functionNameBasic)
{
    testFunctionName1();
}

TEST(LoggerTest, functionNameDouble)
{
    foo::testFunctionName2();
}


TEST(LoggerTest, functionNameTriple)
{
    foo::baz::testFunctionName3();
}

TEST(LoggerTest, trimmedStringShorterThanMax)
{
    std::string expected("abcdefghijklmnopqrstuvwxyz");
    ASSERT_EQ(expected, GetTrimmedString(expected, 50));
}

TEST(LoggerTest, trimmedStringLongerThanMax)
{
    std::string input("abcdefghijklmnopqrstuvwxyz");
    std::string expected("qrstuvwxyz");
    ASSERT_EQ(expected, GetTrimmedString(input, 10));
}
