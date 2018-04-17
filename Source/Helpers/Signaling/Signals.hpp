#ifndef SIGNALS_HPP
#define SIGNALS_HPP

#include <memory>
#include <vector>
#include <algorithm>
#include <optional>

namespace jukebox::signals {

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
        signal.emplace(sig);
    }
    
    void remove()
    {
        signal.reset();
    }

    std::optional<Signal<Args...>*> signal;
};

template<class T, typename ReturnType, class... Args>
class ConcreteSlot : public AbstractSlot<Args...>
{
public:
    ConcreteSlot(T* t, ReturnType(T::*func)(Args...), Signal<Args...>& sig);
    ConcreteSlot(const ConcreteSlot&) = delete;
    ConcreteSlot& operator=(const ConcreteSlot&) = delete;

private:
    friend class Signal<Args...>;

    void call(Args... args) override
    {
        (t->*func)(args...);
    }

    T *t;
    ReturnType(T::*func)(Args...);
};

template<class... Args>
class Signal
{
public:
    Signal() = default;
    Signal(const Signal&) = delete;
    Signal& operator=(const Signal&) = delete;

    ~Signal()
    {
        for(auto i: abstactSlots)
        {
            i->remove();
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

    void operator()(Args&&... args)
    {
        for(auto i: abstactSlots)
        {
            i->call(std::forward<Args>(args)...);
        }
    }

private:
    std::vector<AbstractSlot<Args...>*> abstactSlots;
};

template<class... Args> 
AbstractSlot<Args...>::~AbstractSlot()
{
    if(signal.has_value())
    {
        signal.value()->disconnect(*this);
    }
}

template<class T, typename ReturnType, class... Args>
ConcreteSlot<T, ReturnType, Args...>::ConcreteSlot(T* t_, ReturnType(T::*func_)(Args...), Signal<Args...>& sig)
  : t(t_),
    func(func_)
{
    sig.connect(*this);
}

class Slot
{
public:
    Slot() = default;
    Slot(const Slot&) = delete;
    Slot& operator=(const Slot&) = delete;

    template<class T, typename ReturnType, class... Args>
    void connect(T* t, ReturnType(T::*func)(Args...), Signal<Args...>& sig)
    {
        baseSlots.emplace_back(std::make_unique<ConcreteSlot<T, ReturnType, Args...>>(t, func, sig));
    }

private:
    std::vector<std::unique_ptr<BaseSlot>> baseSlots;
};

}

#endif //SIGNALS_HPP
