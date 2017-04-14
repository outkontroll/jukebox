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
    virtual ~BaseSlot() = default;
};

template<class... Args> 
class AbstractSlot : public BaseSlot
{
protected:
    virtual ~AbstractSlot();
    
    virtual void call(Args... args) = 0;

    friend class Signal<Args...>;

    void add(Signal<Args...>* sig)
    {
        sigs.push_back(sig);
    }
    
    void remove(Signal<Args...>* sig)
    {
        sigs.erase(std::remove(sigs.begin(), sigs.end(), sig), sigs.end());
    }

    std::vector<Signal<Args...>*> sigs;
};

template<class T, class... Args>
class ConcreteSlot : public AbstractSlot<Args...>
{
public:
    ConcreteSlot(T* t, void(T::*func)(Args...), Signal<Args...>& sig);

private:
    ConcreteSlot(const ConcreteSlot&) = delete;
    ConcreteSlot& operator=(const ConcreteSlot&) = delete;

    friend class Signal<Args...>;

    void call(Args... args) override
    {
        (t->*func)(args...);
    }

    T *t;
    void(T::*func)(Args...);
};

template<class... Args>
class Signal
{
public:
    Signal() = default;
    
    ~Signal()
    {
        for(auto i: abstactSlots)
        {
            i->remove(this);
        }
    }

    void connect(AbstractSlot<Args...>& abstractSlot)
    {
        abstactSlots.push_back(&abstractSlot);
        abstractSlot.add(this);
    }
    
    void disconnect(AbstractSlot<Args...>& abstractSlot)
    {
        abstactSlots.erase(std::remove(abstactSlots.begin(), abstactSlots.end(), &abstractSlot), abstactSlots.end());
    }

    void operator()(Args... args)
    {
        for(auto i: abstactSlots)
        {
            i->call(args...); 
        }
    }

private:
    Signal(const Signal&) = delete;
    Signal& operator=(const Signal&) = delete;

    std::vector<AbstractSlot<Args...>*> abstactSlots;
};

template<class... Args> 
AbstractSlot<Args...>::~AbstractSlot()
{
    for(auto i : sigs)
    {
        i->disconnect(*this);
    }
}

template<class T, class... Args> 
ConcreteSlot<T, Args...>::ConcreteSlot(T* t, void(T::*func)(Args...), Signal<Args...>& sig)
: t(t),
    func(func)
{
    sig.connect(*this);
}

class Slot
{
public:
    Slot() = default;
    
    ~Slot()
    {
        for(auto i: baseSlots)
        {
            delete i;
        }
    }

    template<class T, class... Args>
    void connect(T* t, void(T::*func)(Args...), Signal<Args...>& sig)
    {
        baseSlots.push_back(new ConcreteSlot<T, Args...>(t, func, sig));
    }

private:
    Slot(const Slot&) = delete;
    Slot& operator=(const Slot&) = delete;

    std::vector<BaseSlot*> baseSlots;
};

}}

#endif //SIGNALS_HPP
