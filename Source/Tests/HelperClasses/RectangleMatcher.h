#ifndef RECTANGLEMATCHER_H
#define RECTANGLEMATCHER_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "JuceHeader.h"

MATCHER_P(RectangleFloatEquals, rect, ""){
    return testing::Value(arg.getX(), testing::FloatEq(rect.getX())) &&
           testing::Value(arg.getY(), testing::FloatEq(rect.getY())) &&
           testing::Value(arg.getWidth(), testing::FloatEq(rect.getWidth())) &&
           testing::Value(arg.getHeight(), testing::FloatEq(rect.getHeight()));
}

class RectangleFloatNearMatcher
{
public:
    RectangleFloatNearMatcher(float precision_) : precision(precision_) {}

    template <typename T1, typename T2>
    bool MatchAndExplain(const testing::tuple<T1, T2>& a_pair, testing::MatchResultListener*) const
    {
        using namespace testing;
        using testing::get;
        const auto& arg = get<0>(a_pair);
        const auto& rect = get<1>(a_pair);

        return (Value(arg.getX(), FloatNear(rect.getX(), precision)) &&
            Value(arg.getY(), FloatNear(rect.getY(), precision)) &&
            Value(arg.getWidth(), FloatNear(rect.getWidth(), precision)) &&
            Value(arg.getHeight(), FloatNear(rect.getHeight(), precision)));
    }

    void DescribeTo(std::ostream* os) const
    {
        *os << "are a pair where the elements are considered equals if difference is lower than " << precision;
    }

    void DescribeNegationTo(std::ostream* os) const
    {
        *os << "are a pair where the elements are not considered equals if difference is bigger than " << precision;
    }

private:
    const float precision;
};

testing::PolymorphicMatcher<RectangleFloatNearMatcher> RectangleFloatNear(float precision)
{
    return testing::MakePolymorphicMatcher(RectangleFloatNearMatcher(precision));
}

#endif //RECTANGLEMATCHER_H
