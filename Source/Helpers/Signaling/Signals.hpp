#ifndef SIGNALS_HPP
#define SIGNALS_HPP


#include <vector>
#include <algorithm>

namespace jukebox{ namespace signals{

template<class... Args>
class Signal;

class BaseSlot
{
public:
    virtual ~BaseSlot(){}
};

template<class... Args> 
class AbstractSlot : public BaseSlot
{
protected:
    virtual ~AbstractSlot();
    
    virtual void call(Args... args) = 0;

    friend class Signal<Args...>;

    void add(Signal<Args...> *s)
    {
        v.push_back(s);
    }
    
    void remove(Signal<Args...> *s)
    {
        v.erase(std::remove(v.begin(), v.end(), s), v.end());
    }

    std::vector<Signal<Args...>*> v;
};

template<class T, class... Args>
class ConcreteSlot : public AbstractSlot<Args...>
{
public:
    ConcreteSlot(T *t, void(T::*f)(Args...), Signal<Args...> &s);

private:
    ConcreteSlot(const ConcreteSlot&);
    ConcreteSlot& operator=(const ConcreteSlot&);

    friend class Signal<Args...>;

    virtual void call(Args... args)
    {
        (t->*f)(args...); 
    }

    T *t;
    void(T::*f)(Args...);
};

template<class... Args>
class Signal
{
public:
    Signal(){}
    
    ~Signal()
    {
        for(auto i: v)
        {
            i->remove(this);
        }
    }

    void connect(AbstractSlot<Args...> &s)
    {
        v.push_back(&s);
        s.add(this);
    }
    
    void disconnect(AbstractSlot<Args...> &s)
    {
        v.erase(std::remove(v.begin(), v.end(), &s), v.end());
    }

    void operator()(Args... args)
    {
        for(auto i: v)
        {
            i->call(args...); 
        }
    }

private:
    Signal(const Signal&);
    Signal& operator=(const Signal&);

    std::vector<AbstractSlot<Args...>*> v;
};

template<class... Args> 
AbstractSlot<Args...>::~AbstractSlot()
{
    for(auto i : v)
    {
        i->disconnect(*this);
    }
}

template<class T, class... Args> 
ConcreteSlot<T, Args...>::ConcreteSlot(T *t, void(T::*f)(Args...), Signal<Args...> &s)
: t(t),
    f(f)
{
    s.connect(*this);
}

class Slot
{
public:
    Slot(){}
    
    ~Slot()
    {
        for(auto i: v)    
        {
            delete i;
        }
    }

    template<class T, class... Args>
    void connect(T *t, void(T::*f)(Args...), Signal<Args...> &s)
    {
        v.push_back(new ConcreteSlot<T, Args...>(t, f, s));
    }

private:
    Slot(const Slot&);
    Slot& operator=(const Slot&);

    std::vector<BaseSlot*> v;
};

}}

#endif //SIGNALS_HPP
