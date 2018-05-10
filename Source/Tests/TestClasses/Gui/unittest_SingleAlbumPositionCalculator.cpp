#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "SingleAlbumPositionCalculator.h"
#include "RectangleMatcher.h"
#include "Song.h"

using namespace testing;
using namespace jukebox::gui;
using namespace juce;

TEST(SingleAlbumPositionCalculatorTest, imagePlace)
{
    SingleAlbumPositionCalculator calc(100, 100, 10);

    const Rectangle<float> expected{20.185f, 45.0f, 10.0f, 10.f};

    ASSERT_THAT(calc.calculateImagePlace(), RectangleFloatEquals(expected));
}

TEST(SingleAlbumPositionCalculatorTest, albumTextPlace)
{
    SingleAlbumPositionCalculator calc(100, 100, 10);

    const Rectangle<float> expected{30.185f, 10.0f, 50.0f, 24.f};

    ASSERT_THAT(calc.calculateAlbumTextPlace(), RectangleFloatEquals(expected));
}

TEST(SingleAlbumPositionCalculatorTest, artistTextPlace)
{
    SingleAlbumPositionCalculator calc(100, 100, 10);

    const Rectangle<float> expected{40.185f, 10.0f, 50.0f, 24.f};

    ASSERT_THAT(calc.calculateArtistTextPlace(), RectangleFloatEquals(expected));
}

#ifdef NDEBUG
TEST(SingleAlbumPositionCalculatorDeathTest, DISABLED_calculateSelectionBounds_assertIfMaxLineWidthIsZero)
#else
TEST(SingleAlbumPositionCalculatorDeathTest, calculateSelectionBounds_assertIfMaxLineWidthIsZero)
#endif
{
    SingleAlbumPositionCalculator calc(100, 100, 10);

    ASSERT_DEATH(calc.calculateSelectionBounds({}, {1, 1, 0}), "");
}

TEST(SingleAlbumPositionCalculatorTest, calculateSelectionBounds_empty)
{
    SingleAlbumPositionCalculator calc(100, 100, 10);

    ASSERT_THAT(calc.calculateSelectionBounds({}, {1, 1, 1}), IsEmpty());
}

TEST(SingleAlbumPositionCalculatorTest, calculateSelectionBounds_multipleSelections)
{
    SingleAlbumPositionCalculator calc(100, 100, 10);
    const auto result = calc.calculateSelectionBounds({{0, 0, "", "001abcd123"}, {0, 0, "", "002A"}, {0, 0, "", "003Qwerty12345"}}, {100, 100, 50});

    const decltype(result) expected{{96, 77.552f, 58, 54},
                                    {96, 125.552f, 58, 30},
                                    {96, 149.552f, 58, 78}};
    ASSERT_THAT(result, testing::Pointwise(RectangleFloatNear(1e-03f), expected));
}

TEST(SingleAlbumPositionCalculatorTest, calculateSelectionBounds_veryLongLine)
{
    SingleAlbumPositionCalculator calc(1000, 1000, 100);

    const auto result = calc.calculateSelectionBounds({{0, 0, "", "001abcdefghijklmnopqrtst uvwxyz1234567890"}}, {100, 100, 50});
    const std::vector<Rectangle<float>> expected{{96, 77.552f, 58, 222}};

    ASSERT_THAT(result, testing::Pointwise(RectangleFloatNear(1e-03f), expected));
}

TEST(SingleAlbumPositionCalculatorTest, drawableSonNamesPlace)
{
    SingleAlbumPositionCalculator calc(100, 100, 10);

    const auto [result1, result2, result3] = calc.calculateDrawableSongNamesPlace();

    ASSERT_EQ(40, result1);
    ASSERT_EQ(45, result2);
    ASSERT_EQ(50, result3);
}

TEST(MacherTest, describeTo)
{
    RectangleFloatNearMatcher matcher(123456);

    std::ostringstream os;
    matcher.DescribeTo(&os);

    ASSERT_NE(std::string::npos, os.str().find("123456"));
}

TEST(MacherTest, describeNegationTo)
{
    RectangleFloatNearMatcher matcher(123456);

    std::ostringstream os;
    matcher.DescribeNegationTo(&os);

    ASSERT_NE(std::string::npos, os.str().find("123456"));
}
