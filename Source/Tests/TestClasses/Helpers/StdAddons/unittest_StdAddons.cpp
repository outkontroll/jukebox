#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "StdAddons.hpp"

TEST(StdAddonsTest, transform_exclusive_scan)
{
    std::vector<int> resVec1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> resVec2(resVec1.size());
    std_addons::transform_exclusive_scan(resVec1,
                                         resVec2.begin(),
                                         0,
                                         std::plus<>(),
                                         [](int arg){ return arg *= arg; });

    std::vector<int> expected{0, 1, 5, 14, 30, 55, 91, 140, 204};
    ASSERT_THAT(resVec2, testing::Pointwise(testing::Eq(), expected));
}

TEST(StdAddonsTest, accumulate)
{
    std::vector<int> resVec1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    const auto expected = std::accumulate(resVec1.begin(), resVec1.end(), 1, std::plus<>());

    ASSERT_EQ(expected, std_addons::accumulate(resVec1, 1, std::plus<>()));
}

TEST(StdAddonsTest, sort)
{
    std::vector<int> resVec1{15, 29, 3, 47, 5, 16, -17, 8, 0};
    std::vector<int> resVec2(resVec1.begin(), resVec1.end());

    std::sort(resVec1.begin(), resVec1.end());
    std_addons::sort(resVec2);

    ASSERT_THAT(resVec1, testing::Pointwise(testing::Eq(), resVec2));
}

TEST(StdAddonsTest, sort2)
{
    std::vector<int> resVec1{15, 29, 3, 47, 5, 16, -17, 8, 0};
    std::vector<int> resVec2(resVec1.begin(), resVec1.end());

    std::sort(resVec1.begin(), resVec1.end(), std::less<>());
    std_addons::sort(resVec2, std::less<>());

    ASSERT_THAT(resVec1, testing::Pointwise(testing::Eq(), resVec2));
}

TEST(StdAddonsTest, transform)
{
    std::vector<int> resVec1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> resVec2;
    resVec2.reserve(resVec1.size());
    std::vector<int> resVec3;
    resVec3.reserve(resVec1.size());

    std::transform(resVec1.begin(), resVec1.end(), std::back_inserter(resVec2), [](const auto i) { return i * i; });
    std_addons::transform(resVec1, std::back_inserter(resVec3), [](const auto i) { return i * i; });

    ASSERT_THAT(resVec3, testing::Pointwise(testing::Eq(), resVec2));
}

TEST(StdAddonsTest, transform2)
{
    std::vector<int> resVec1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> resVec4{10, 20, 30, 40, 50, 60, 70, 80, 90};
    std::vector<int> resVec2;
    resVec2.reserve(resVec1.size());
    std::vector<int> resVec3;
    resVec3.reserve(resVec1.size());

    std::transform(resVec1.begin(), resVec1.end(), resVec4.begin(), std::back_inserter(resVec2), std::plus<>());
    std_addons::transform(resVec1, resVec4, std::back_inserter(resVec3), std::plus<>());

    ASSERT_THAT(resVec3, testing::Pointwise(testing::Eq(), resVec2));
}
