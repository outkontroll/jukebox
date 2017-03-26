#ifndef SCOPEGUARD_HPP
#define SCOPEGUARD_HPP

namespace jukebox {

template<class T>
class ScopeGuard
{
public:
    ScopeGuard(T& capture, T valueToSet)
    :   capturedData(capture),
        oldValue(capture)
    {
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
