#ifndef FREEFUNCTIONS_H
#define FREEFUNCTIONS_H

#include "Song.h"
#include "gmock/gmock.h"

struct IFoo
{
    virtual ~IFoo() = default;
    virtual void foo() = 0;
    virtual void fooSong(const jukebox::audio::Song&) = 0;
    virtual void fooString(const std::string&) = 0;
};

struct FooMock : public IFoo
{
    MOCK_METHOD0(foo, void());
    MOCK_METHOD1(fooSong, void(const jukebox::audio::Song&));
    MOCK_METHOD1(fooString, void(const std::string&));
};

#endif // FREEFUNCTIONS_H
