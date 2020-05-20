#ifndef RECTANGLEMATCHER_H
#define RECTANGLEMATCHER_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "JuceHeader.h"

namespace juce {

void PrintTo(const Rectangle<float>& r, std::ostream* os);

}

MATCHER_P(RectangleFloatEquals, rect, "")
{
    using namespace testing;
    return Value(arg.getX(), FloatEq(rect.getX())) &&
           Value(arg.getY(), FloatEq(rect.getY())) &&
           Value(arg.getWidth(), FloatEq(rect.getWidth())) &&
           Value(arg.getHeight(), FloatEq(rect.getHeight()));
}

MATCHER_P2(RectangleFloatNear, rect, precision, "")
{
    using namespace testing;
    return (Value(arg.getX(), FloatNear(rect.getX(), precision)) &&
            Value(arg.getY(), FloatNear(rect.getY(), precision)) &&
            Value(arg.getWidth(), FloatNear(rect.getWidth(), precision)) &&
            Value(arg.getHeight(), FloatNear(rect.getHeight(), precision)));
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

inline testing::PolymorphicMatcher<RectangleFloatNearMatcher> RectangleFloatNear(float precision)
{
    return testing::MakePolymorphicMatcher(RectangleFloatNearMatcher(precision));
}

#endif //RECTANGLEMATCHER_H
