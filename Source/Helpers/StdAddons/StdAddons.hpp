#ifndef STDADDONS_H
#define STDADDONS_H

#include <utility>
#include <numeric>
#include <algorithm>

namespace std_addons {

template<class InputIterator1, class InputIterator2, class OutputIterator, class T, class BinaryOperator, class UnaryOperator>
OutputIterator transform_exclusive_scan(InputIterator1 first,
                                        InputIterator2 last,
                                        OutputIterator result,
                                        T init,
                                        BinaryOperator outerOp,
                                        UnaryOperator innerOp)
{
    for (; first != last; ++first, ++result)
    {
        *result = init;
        init = outerOp(init, innerOp(*first));
    }
    return result;
}

template<typename Range, class OutputIterator, class T, class BinaryOperator, class UnaryOperator>
OutputIterator transform_exclusive_scan(Range&& range,
                                        OutputIterator&& result,
                                        T&& init,
                                        BinaryOperator&& outerOp,
                                        UnaryOperator&& innerOp)
{
    return transform_exclusive_scan(std::begin(range),
                                    std::end(range),
                                    std::forward<OutputIterator>(result),
                                    std::forward<T>(init),
                                    std::forward<BinaryOperator>(outerOp),
                                    std::forward<UnaryOperator>(innerOp));
}

template<typename Range, typename T>
T accumulate(Range&& range, T init)
{
    return std::accumulate(std::begin(range), std::end(range), init);
}

template<typename Range, typename T, typename BinaryOperation>
T accumulate(Range&& range, T init, BinaryOperation&& op)
{
    return std::accumulate(std::begin(range), std::end(range), init, std::forward<BinaryOperation>(op));
}

template<typename Range>
void sort(Range&& range)
{
    std::sort(std::begin(range), std::end(range));
}

template<typename Range, typename Compare>
void sort(Range&& range, Compare&& comp)
{
    std::sort(std::begin(range), std::end(range), std::forward<Compare>(comp));
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
