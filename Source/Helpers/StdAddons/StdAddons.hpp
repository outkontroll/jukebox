#ifndef STDADDONS_H
#define STDADDONS_H

#include <utility>
#include <numeric>
#include <algorithm>

namespace std_addons {

template<class InputIterator1, class InputIterator2, class OutputIterator, class BinaryOperator, class UnaryOperator, class T>
OutputIterator transform_exclusive_scan(InputIterator1 first,
                                        InputIterator2 last,
                                        OutputIterator result,
                                        BinaryOperator outerOp,
                                        UnaryOperator innerOp,
                                        T init)
{
    for (; first != last; ++first, ++result)
    {
        *result = init;
        init = outerOp(init, innerOp(*first));
    }
    return result;
}

template<typename Range, class OutputIterator, class BinaryOperator, class UnaryOperator, class T>
OutputIterator transform_exclusive_scan(Range&& range,
                                        OutputIterator&& result,
                                        BinaryOperator&& outerOp,
                                        UnaryOperator&& innerOp,
                                        T&& init)
{
    return transform_exclusive_scan(std::begin(range),
                                    std::end(range),
                                    std::forward<OutputIterator>(result),
                                    std::forward<BinaryOperator>(outerOp),
                                    std::forward<UnaryOperator>(innerOp),
                                    std::forward<T>(init));
}

template<typename Range1, typename T, typename BinaryOperation>
T accumulate(Range1&& range, T init, BinaryOperation&& op)
{
    return std::accumulate(std::begin(range), std::end(range), init, std::forward<BinaryOperation>(op));
}

template<typename Range1, typename OutputIterator, typename UnaryOperator>
OutputIterator transform(Range1&& range1,
                         OutputIterator&& result,
                         UnaryOperator&& op)
{
    return std::transform(std::begin(range1), std::end(range1), std::forward<OutputIterator>(result), std::forward<UnaryOperator>(op));
}

template<typename Range1, typename Range2, class OutputIterator, class BinaryOperator>
OutputIterator transform(Range1&& range1,
                         Range2&& range2,
                         OutputIterator&& result,
                         BinaryOperator&& op)
{
    return std::transform(std::begin(range1), std::end(range1), std::begin(range2), std::forward<OutputIterator>(result), std::forward<BinaryOperator>(op));
}

}

#endif //STDADDONS_H
