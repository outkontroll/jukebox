#ifndef FREEFUNCTIONS_H
#define FREEFUNCTIONS_H

#include "gmock/gmock.h"

struct IFoo
{
    virtual void foo() = 0;
};

struct FooMock : public IFoo
{
    MOCK_METHOD0(foo, void());
};

#endif // FREEFUNCTIONS_H
