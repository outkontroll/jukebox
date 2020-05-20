#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MultipleAlbumsCanvasPositionCalculator.h"
#include "RectangleMatcher.h"

using namespace testing;
using namespace jukebox::gui;
using namespace juce;

namespace {

constexpr auto scale = 1.2f;
constexpr auto precision = 1e-4f;

auto checkForBoundaries = [](const auto& rect, int column, int row, float slotWidth, float slotHeight) {
    ASSERT_GE(rect.getX(), slotWidth * column);
    ASSERT_LE(rect.getX(), slotWidth * (column + 1));
    ASSERT_GE(rect.getY(), slotHeight * row);
    ASSERT_LE(rect.getY(), slotHeight * (row + 1));
    ASSERT_GE(rect.getWidth(), 0);
    ASSERT_LE(rect.getWidth(), slotWidth);
    ASSERT_LE(rect.getWidth(), slotHeight);
    ASSERT_GE(rect.getHeight(), 0);
    ASSERT_LE(rect.getHeight(), slotWidth);
    ASSERT_LE(rect.getHeight(), slotHeight);
};

auto BoundariesTestNameGenerator = [](const auto& info) -> std::string
{
    const float width = std::get<0>(std::get<0>(info.param));
    const float height = std::get<1>(std::get<0>(info.param));
    const int column = std::get<0>(std::get<1>(info.param));
    const int row = std::get<1>(std::get<1>(info.param));
    if(fabs(width * scale - height) < precision)
        return "basic_" + std::to_string(column) + "_" + std::to_string(row);
    else if(width * scale < height)
        return "high_" + std::to_string(column) + "_" + std::to_string(row);
    else
        return "wide_" + std::to_string(column) + "_" + std::to_string(row);
};

}

class Boundaries : public TestWithParam<std::tuple<std::tuple<float, float>, std::tuple<int, int>>>
{
public:
    void SetUp() override
    {
        std::tuple<float, float> size;
        std::tuple<int, int> indices;
        std::tie(size, indices) = GetParam();
        slotWidth = std::get<0>(size);
        slotHeight = std::get<1>(size);
        albumIndex = column + row * columns;
        calc = std::make_unique<MultipleAlbumsPositionCalculator>(slotWidth, slotHeight, columns);
    }

protected:
    float slotWidth = 0;
    float slotHeight = 0;
    int column = 0;
    int row = 0;
    int albumIndex = 0;
    std::unique_ptr<MultipleAlbumsPositionCalculator> calc;

    const int columns = 4;
};

TEST_P(Boundaries, ImagePlace)
{
    const auto imagePlace = calc->calculateImagePlace(albumIndex);

    checkForBoundaries(imagePlace, column, row, slotWidth, slotHeight);
}

TEST_P(Boundaries, TextPlace)
{
    const auto textPlace = calc->calculateTextPlace2(albumIndex);

    checkForBoundaries(textPlace, column, row, slotWidth, slotHeight);
}

TEST_P(Boundaries, SelectionPlace)
{
    const auto imagePlace = calc->calculateImagePlace(albumIndex);

    const auto selectionPlace = calc->calculateSelectionPlace(imagePlace);

    checkForBoundaries(selectionPlace, column, row, slotWidth, slotHeight);
}

INSTANTIATE_TEST_CASE_P(MultipleAlbumsPositionCalculator,
                        Boundaries,
                        Combine(
                            Values(std::make_tuple(400.0f, 480.0f),
                                   std::make_tuple(700.0f, 480.0f),
                                   std::make_tuple(400.0f, 780.0f)),
                            Values(std::make_tuple(0, 0),
                                   std::make_tuple(0, 3),
                                   std::make_tuple(1, 0),
                                   std::make_tuple(3, 4))),
                        BoundariesTestNameGenerator);

TEST(MultipleAlbumsPositionCalculator, basicSlot)
{
    const auto slotWidth = 400.0f;
    const auto slotHeight = 480.0f;
    const auto columns = 4;

    MultipleAlbumsPositionCalculator calc{slotWidth, slotHeight, columns};

    const Rectangle<float> expected{12.0f, 92.0f, 376.0f, 376.0f};

    const auto imagePlace = calc.calculateImagePlace(0);
    ASSERT_THAT(imagePlace, RectangleFloatNear(expected, precision));
}

TEST(MultipleAlbumsPositionCalculator, slotIsWide)
{
    const auto slotWidth = 780.0f;
    const auto slotHeight = 480.0f;
    const auto columns = 4;

    MultipleAlbumsPositionCalculator calc{slotWidth, slotHeight, columns};

    const Rectangle<float> expected{202.0f, 92.0f, 376.0f, 376.0f};

    const auto imagePlace = calc.calculateImagePlace(0);
    ASSERT_THAT(imagePlace, RectangleFloatNear(expected, precision));
}

TEST(MultipleAlbumsPositionCalculator, slotIsHigh)
{
    const auto slotWidth = 400.0f;
    const auto slotHeight = 780.0f;
    const auto columns = 4;

    MultipleAlbumsPositionCalculator calc{slotWidth, slotHeight, columns};

    const Rectangle<float> expected{12.0f, 242.0f, 376.0f, 376.0f};

    const auto imagePlace = calc.calculateImagePlace(0);
    ASSERT_THAT(imagePlace, RectangleFloatNear(expected, precision));
    ASSERT_THAT(sizeof (long long) * 8, 32);
}
