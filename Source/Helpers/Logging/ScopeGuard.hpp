#ifndef SCOPEGUARD_HPP
#define SCOPEGUARD_HPP

#include <type_traits>

namespace jukebox {

template<class T>
class ScopeGuard
{
public:
    ScopeGuard(T& capture, T valueToSet)
    :   capturedData(capture),
        oldValue(capture)
    {
        static_assert(std::is_copy_assignable<T>::value, "Can not assign value!");
        capturedData = valueToSet;
    }

    ~ScopeGuard()
    {
        capturedData = oldValue;
    }

private:
    T& capturedData;
    T oldValue;
};

}

#endif //SCOPEGUARD_HPP
