#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "StdAddons.hpp"

TEST(StdAddonsTest, transform_exclusive_scan)
{
    const std::vector<int> input{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> result(input.size());
    std_addons::transform_exclusive_scan(input, result.begin(), 0, std::plus<>(), [](int arg){
        return arg *= arg;
    });

    const std::vector<int> expected{0, 1, 5, 14, 30, 55, 91, 140, 204};
    ASSERT_THAT(result, testing::Pointwise(testing::Eq(), expected));
}

TEST(StdAddonsTest, accumulate)
{
    const std::vector<int> input{1, 2, 3, 4, 5, 6, 7, 8, 9};
    const auto expected = std::accumulate(input.begin(), input.end(), 1);

    ASSERT_EQ(expected, std_addons::accumulate(input, 1));
}

TEST(StdAddonsTest, accumulateBinary)
{
    const std::vector<int> input{1, 2, 3, 4, 5, 6, 7, 8, 9};
    const auto expected = std::accumulate(input.begin(), input.end(), 1, std::plus<>());

    ASSERT_EQ(expected, std_addons::accumulate(input, 1, std::plus<>()));
}

TEST(StdAddonsTest, sort)
{
    std::vector<int> input{15, 29, 3, 47, 5, 16, -17, 8, 0};
    std::vector<int> result(input.begin(), input.end());

    std::sort(input.begin(), input.end());
    std_addons::sort(result);

    ASSERT_THAT(input, testing::Pointwise(testing::Eq(), result));
}

TEST(StdAddonsTest, sortWithComparator)
{
    std::vector<int> input{15, 29, 3, 47, 5, 16, -17, 8, 0};
    std::vector<int> result(input.begin(), input.end());

    std::sort(input.begin(), input.end(), std::less<>());
    std_addons::sort(result, std::less<>());

    ASSERT_THAT(input, testing::Pointwise(testing::Eq(), result));
}

TEST(StdAddonsTest, transformUnary)
{
    const std::vector<int> input{1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::vector<int> expected;
    expected.reserve(input.size());
    std::vector<int> result;
    result.reserve(input.size());

    std::transform(input.begin(), input.end(), std::back_inserter(expected), [](const auto i) { return i * i; });
    std_addons::transform(input, std::back_inserter(result), [](const auto i) { return i * i; });

    ASSERT_THAT(result, testing::Pointwise(testing::Eq(), expected));
}

TEST(StdAddonsTest, transformBinary)
{
    const std::vector<int> input{1, 2, 3, 4, 5, 6, 7, 8, 9};
    const std::vector<int> input2{10, 20, 30, 40, 50, 60, 70, 80, 90};

    std::vector<int> expected;
    expected.reserve(input.size());
    std::vector<int> result;
    result.reserve(input.size());

    std::transform(input.begin(), input.end(), input2.begin(), std::back_inserter(expected), std::plus<>());
    std_addons::transform(input, input2, std::back_inserter(result), std::plus<>());

    ASSERT_THAT(result, testing::Pointwise(testing::Eq(), expected));
}
